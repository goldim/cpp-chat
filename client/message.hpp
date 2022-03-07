#ifndef MESSAGE_HPP
#define	MESSAGE_HPP

#include <cstring>
#include <string>
#include <ctime>
#include <boost/date_time.hpp>
#include "clientid.hpp"

class Message
{
    public:
        IDClient id;
        time_t sendTime;
        std::string text;
        friend std::ostream &operator<<(std::ostream& out, const Message &msg);
        Message(){};
        Message(IDClient &_id, std::string _text = "", time_t _time = time(0));
        Message(std::string str);
        IDClient get_id() const;
};


#endif	/* MESSAGE_HPP */


