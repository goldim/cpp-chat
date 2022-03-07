#ifndef CONNECTION_HPP
#define	CONNECTION_HPP

#include <sstream>
#include <string>
#include "interface.cpp"
#include "clientid.hpp"
#include "message.hpp"
#include "boost_serializer.hpp"
#include "id_generator.hpp"
#include "ioc_container.hpp"

/**
 * @brief Служит для хранения информации об входящих соединениях, отправке
 * и получении сообщений
 * 
 * @class Connection
 * @author Золотов Д. <goldim1993@mail.ru>
 */
class Connection: public IConnection
{
        IDClient id;
        IClientSocket *sock;
        std::shared_ptr<ISerializer<Message>> serializer;
        char *buffer;
        int sizeBuffer;
    public:
        Connection();
        ~Connection();
        void init(IClientSocket *csock, int size = 0);
        void transmit(Message &msg);
        void stop();
        /**
         * Получает с помощью сокетов сериализованный объект класса сообщения
         * и преобразует его в обычный объект класса сообщения
         * @return Сообщение
         */
        Message *receive();
        std::string client_info() const;
};

#endif	/* CONNECTION_HPP */

