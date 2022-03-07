#ifndef CORE_H
#define	CORE_H

#include <string>
#include <boost/property_tree/ini_parser.hpp>
#include "message.hpp"
#include "socket_exception.hpp"
#include "interface.cpp"

class Client
{
    private:
        IDClient *id;
        boost::property_tree::ptree cfg;
        std::shared_ptr< IClientSocket > sock;
        std::shared_ptr<ISerializer<Message>> serializer;
        std::shared_ptr<ISerializer<IDClient>> idserializer;
        int bufferSize;
        char *buffer;
    public:
        std::string login;
        Client(std::string _ip, int _port, std::string _login);
        ~Client();
        void start() throw(SocketException);
        void send_msg(std::string text);
        std::string receive_msg();
};      


#endif	

