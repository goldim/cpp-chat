#ifndef SOCKET_EXCEPTION_HPP
#define	SOCKET_EXCEPTION_HPP

#include <exception>
#include <string>

class SocketException: std::exception 
{
        std::string info;
    public:        
        SocketException(const char* s);
        ~SocketException() throw(){}
        /**
         * @brief Выводит информацию об исключении
         * 
         * @return краткое информационное сообщение об ошибке
         */
        std::string what();
};


#endif	/* SOCKET_EXCEPTION_HPP */

