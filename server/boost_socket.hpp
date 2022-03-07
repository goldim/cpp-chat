#ifndef BOOST_SOCKET_HPP
#define	BOOST_SOCKET_HPP

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/ip/address.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include "socket_exception.hpp"
#include "interface.cpp"

/**
 * @brief реализация сокетов с помощью библиотеки boost
 * @class BoostClientSocket
 */
class BoostClientSocket:public IClientSocket
{
    public:
        BoostClientSocket(){};
        BoostClientSocket(boost::asio::ip::tcp::socket *sock, boost::asio::io_service *ioser);
        BoostClientSocket(std::string ip, int port);
        ~BoostClientSocket();
        std::string info() const;
        void connect();
        int receive(char *data, int size) const;
        void send(std::string data, int size) const;
        void stop();
    private:
        boost::asio::io_service *ios;
        boost::asio::ip::tcp::endpoint *endpoint;
        boost::asio::ip::tcp::socket *socket;        
};

/**
 * @brief реализация сокетов с помощью библиотеки boost
 * @class BoostServerSocket
 */
class BoostServerSocket:public IServerSocket
{
    public:
        BoostServerSocket(){};
        BoostServerSocket(std::string ip, int port, int size);
        ~BoostServerSocket();
        IClientSocket *accept();
        void bind();        
        std::string info() const;
        void listen() const;        
        void stop();
    private:
        boost::asio::ip::tcp::endpoint *endpoint;
        boost::asio::ip::tcp::acceptor *acceptor;
        int queueSize;
};


#endif	/* BOOST_SOCKET_HPP */

