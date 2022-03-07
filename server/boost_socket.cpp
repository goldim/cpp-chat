#include "boost_socket.hpp"
#include <iostream>

using namespace boost::asio;

BoostClientSocket::BoostClientSocket(ip::tcp::socket *sock, io_service *ioser)
{
    socket = sock;    
    ios = ioser;
}

BoostClientSocket::BoostClientSocket(std::string ip, int port) 
{
    ios = new io_service();
    ip::address address = ip::address::from_string(ip.c_str());
    endpoint = new ip::tcp::endpoint(address, port); 
    socket =   new ip::tcp::socket(*ios);         
}

void BoostClientSocket::stop()
{
    socket->shutdown(ip::tcp::socket::shutdown_both);
}

void BoostClientSocket::connect()
{    
    socket->connect(*endpoint);
}

int BoostClientSocket::receive(char *data, int size) const 
{
    boost::system::error_code error;
    int dataSize = socket->read_some(buffer((void *)data, size), error);
    return (error != 0) ? 0 : dataSize;
}

void BoostClientSocket::send(std::string data, int size) const
{
    socket->send(buffer(data.c_str(), size));
}

std::string BoostClientSocket::info() const
{
    return socket->remote_endpoint().address().to_string();
}

BoostClientSocket::~BoostClientSocket() 
{
    socket->close();
    delete ios, endpoint;
}

BoostServerSocket::BoostServerSocket(std::string ip, int port, int size) 
{
    io_service io_service; 
    ip::address address = ip::address::from_string(ip.c_str());
    endpoint = new ip::tcp::endpoint(address, port); 
    boost::asio::socket_base::reuse_address option(true);
    acceptor = new ip::tcp::acceptor(io_service);
    acceptor->open(ip::tcp::v4());
    acceptor->set_option(option);
    queueSize = size;
}

void BoostServerSocket::bind() 
{
    acceptor->bind(*endpoint);
}

void BoostServerSocket::listen() const
{
    acceptor->listen(queueSize);
}

IClientSocket *BoostServerSocket::accept() 
{
    io_service *ios = new io_service();
    ip::tcp::socket *acceptedSocket = new ip::tcp::socket(*ios);
    acceptor->accept(*acceptedSocket); 
    return new BoostClientSocket(acceptedSocket, ios);
}

std::string BoostServerSocket::info() const
{
    return endpoint->address().to_string();
}

void BoostServerSocket::stop()
{
    acceptor->close();
}

BoostServerSocket::~BoostServerSocket() 
{
    acceptor->close();
    delete endpoint;
}