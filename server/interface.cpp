#ifndef INTERFACE_CPP
#define	INTERFACE_CPP

#include <string>

class Message;

/**
 * @brief интерфейс сокета, который выполняет функции отправки, получения данных
 * @interface IClientSocket
 */
class IClientSocket
{
    public: 
        /**
         * @brief Подключается к прослушивающему сокету
         */
        virtual void connect() = 0;
        /**
         * @brief Отправляет данные сокету
         * 
         * @param[in] data отправляемые данные
         */
        virtual void send(std::string data, int size) const = 0;
        /**
         * @brief Принимает данные от сокета
         * 
         * @param[out] data буфер для записи принятых данных
         * @param[in] size размер буфера
         * @return количество принятых символов, в случае завершения соединения 0
         */
        virtual int receive(char *data, int size) const = 0;
        /**
         * @brief Останавливает обслуживание соединения (отправка и получение сообщений)
         */
        virtual void stop() = 0;
        /**
         * @brief Получить краткие сведения о противоположной точке соединения
         * 
         * @return Строку, содержащую ip и порт противоположной точке соединения
         */
        virtual std::string info() const = 0;
        virtual ~IClientSocket(){}
};

/**
 * @brief интерфейс сериализатора, содержащий операции сериализации
 * @interface ISerializer
 * @tparam A сериализируемый класс
 */
template <class A>
class ISerializer
{
public:
    virtual ~ISerializer(){}
    /**
    * @brief Генерирует пригодное для хранения представление класса
    * 
    * @param[in] obj объект, подлежащий сериализации
    * @return Строку, содержащую потоковое представление объекта класса
    */
    virtual std::string serialize(A obj) = 0;
    /**
    * @brief Создает объект из хранимого представления
    * 
    * Обратный процесс сериализации
    * @param[in] input строка, которая содержит представление сериализованного объекта
    * @return указатель на объект 
    */
    virtual A* deserialize(std::string input) = 0;
};

/**
 * @brief Интерфейс поддерживает сетевые операции сервера
 * @interface IServerSocket
 */
class IServerSocket
{
    public: 
        /**
         * @brief Связывает прослушивающий сокет к ip и порту
         */
        virtual void bind() = 0;
        /**
         * @brief Переводит сокет в прослушивающее состояние
         */
        virtual void listen() const = 0;
        /**
         * @brief Принимает входящие соединения
         * 
         * @return Объект обертку сокета
         */
        virtual IClientSocket *accept() = 0;
        /**
         * @brief Останавливает подключение входящих соединений
         */
        virtual void stop() = 0;
        virtual ~IServerSocket(){}

};

/**
 * @brief Инкапсулирует способ хранения сообщений
 * @interface IStorage
 */
class IStorage
{
    public:
        /**
         * @brief Добавляет сообщение в хранилище
         * 
         * @param msg сообщение
         */
        virtual void add(const Message& msg) = 0;
        /**
         * @brief Извлекает сообщение из структуры
         * 
         * @param index индекс структуры данных, в которой хранится сообщение
         * @return Ссылку на сообщение в структуре данных
         */
        virtual Message &select(int index) = 0;
        /**
         * @brief Получает количество сообщений
         * 
         * @return количество сообщенией в структуре хранения данных
         */
        virtual int count() const = 0;
        virtual ~IStorage(){}
};

/**
 * @brief Интерфейс для работы с пользовательскими подключениями
 * @interface IConnection
 */
class IConnection
{
    public:
        /**
         * @brief Инициализирует соединение параметрами (Служит вроде конструктора)
         * 
         * @param[in] csock принятый сокет
         * @param[in] size размер буфера для входящих данных
         */
        virtual void init(IClientSocket *csock, int size) = 0;
         /**
         * @brief Передает сообщение через соединение
         * 
         * Сериализует сообщение и через подключенный сокет передает его
         * на противоположную сторону соединения
         * @param[in] msg объект класса сообщения 
         */
        virtual void transmit(Message &msg) = 0;
        /**
         * @brief Получает сообщение от клиента
         * 
         * @return Сообщение
         */
        virtual Message *receive() = 0;
        /**
         * @brief Останавливает обслуживание соединения (отправка и получение сообщений)
         */
        virtual void stop() = 0;
         /**
         * @brief Получает краткую информацию об отправителе сообщения
         * 
         * @return Строка, содержащая краткую информацию о клиенте, например, такую как
         *  идентификатор отправителя, ip и порт отправителя и т.д.
         */
        virtual std::string client_info() const = 0;
        virtual ~IConnection(){}
};

/*
 * @interface IServer
 */
class IServer
{
    public:
        /**
        * @brief Запускает работу сервера
        * 
        * Принимает входящие соединения, каждому выделяет отдельный поток, 
        * и в этом потоке происходит получение данных от клиента
        */
        virtual void start() = 0;
        /**
        * @brief Приостанавливает работу сервера
        */
        virtual void stop() = 0;
        /**
        * @brief Рассылает сообщение, полученное от одного клиента остальным 
        * 
        * @param[in] msg сообщение
        */
        virtual void send_all(Message &msg) = 0;
        virtual ~IServer(){}
};

#endif
