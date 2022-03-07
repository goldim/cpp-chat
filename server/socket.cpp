#include "socket.hpp"
#include <iostream>

Socket::Socket(int id)
{
    descriptor = id;
}

Socket::Socket(std::string ip, int port, int size) 
{
    address.sin_addr.s_addr = inet_addr(ip.c_str());        
    address.sin_port = htons(port);
    address.sin_family = AF_INET;
    descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (descriptor == -1) throw SocketException("socket");
    queueSize = size;
    int option = 1;
    setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, (char*)&option,sizeof(option));
}

Socket::~Socket() 
{
    close(descriptor);
}

void Socket::stop()
{
    shutdown(descriptor, SHUT_RDWR);
}

int Socket::receive(char *data, int size) const 
{
    return recv(descriptor, (void *)data, size, 0);
}

void Socket::send(std::string data, int size) const
{
    ::send(descriptor, data.c_str(), size, 0);
}

void Socket::bind() 
{
    if (::bind(descriptor, (sockaddr *)&address, sizeof(address)) < 0) throw SocketException("bind");
}

void Socket::listen() const
{
    if (::listen(descriptor, queueSize) < 0) throw SocketException("listen");
}

void Socket::connect() 
{
    if (::connect(descriptor, (sockaddr *)&address, sizeof(address))==-1) throw SocketException("connection error");
}

IClientSocket *Socket::accept() 
{
    socklen_t length = sizeof(address);
    int result = ::accept(descriptor, (sockaddr *)&address, &length);
    if (result == -1) return NULL;
    return new Socket(result);
}

std::string Socket::info() const
{
    return inet_ntoa(address.sin_addr);
}