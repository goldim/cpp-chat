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

#endif
