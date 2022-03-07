#include "socket_exception.hpp"

SocketException::SocketException(const char* s) 
{
     info = s;
}

std::string SocketException::what() 
{
    return info;
}
