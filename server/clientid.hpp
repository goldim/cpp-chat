#ifndef CLIENTID_HPP
#define	CLIENTID_HPP

#include <string>
#include "interface.cpp"

class IDClient
{
    public:
        /**
         * @var уникальный идентификатор объекта класса IDClient
         */
        unsigned id;
        /**
         * @var никнейм или логин клиента
         */
        std::string login;
        /**
         * @brief Выводит строковое представление объекта класса  
         * в поток вывода
         * 
         * @param[out] out поток вывода
         * @param[in] id идентификатор пользователя
         * @return Ссылку на поток вывода с данными об объекте класса IDClient
         */
        friend std::ostream &operator<<(std::ostream& out, const IDClient &id);
        IDClient(int _id = 0, std::string _login = "");
        /**
         * @brief Получает информацию о клиенте
         *  
         * @return Строку, содержащую краткую информацию о клиенте
         */
        std::string ToString() const;
};

#endif	/* CLIENTID_HPP */

