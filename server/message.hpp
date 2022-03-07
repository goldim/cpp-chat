#ifndef MESSAGE_HPP
#define	MESSAGE_HPP

#include <cstring>
#include <string>
#include <ctime>
#include <boost/date_time.hpp>
#include "clientid.hpp"

/**
 * @class Message
 */
class Message
{
    public:
        /**
         * @var уникальный идентификатор клиента 
         */
        IDClient id;
        /**
         * @var время отправки сообщения, определяется на машине клиента
         */
        time_t sendTime;
        /**
         * @var текст сообщения
         */
        std::string text;
        /**
         * @brief Выводит строковое представление объекта класса  
         * в поток вывода
         * 
         * @param[out] out поток вывода
         * @param[in] msg сообщение
         * @return Ссылку на поток вывода с данными об объекте класса Message
         */
        friend std::ostream &operator<<(std::ostream& out, const Message &msg);
        Message(){};
        Message(IDClient &_id, std::string _text = "", time_t _time = time(0));
        Message(std::string str);
        /**
         * @brief Получает объект, который содержит информацию, характеризующую
         * отправителя сообщения
         * 
         * @return уникальный идентификатор клиента
         */
        IDClient get_id() const;
};


#endif	/* MESSAGE_HPP */

