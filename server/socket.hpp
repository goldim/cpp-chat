#ifndef SOCKET_HPP
#define	SOCKET_HPP

#include <sys/socket.h> 
#include <ctype.h> // sockaddr_in
#include <netinet/in.h>
#include <unistd.h> // close()
#include <arpa/inet.h>
#include "socket_exception.hpp"
#include "interface.cpp"

/**
 * @brief Класс для работы с сетью
 * 
 * Работа с сетью реализована через сетевые сокеты
 * В данном случае используются сокеты языка C
 * @class Socket
 */
class Socket:public IServerSocket, public IClientSocket
{
        sockaddr_in address;
        int queueSize;
        int descriptor;
    public:
        Socket(){};
        Socket(int id);
        Socket(std::string ip, int port,int size = 0);
        ~Socket();
        IClientSocket *accept();
        void bind();
        void connect();
        std::string info() const;
        void listen() const;
        int receive(char *data, int size) const;
        void send(std::string data, int size) const;
        void stop();
};


#endif	/* SOCKET_HPP */

