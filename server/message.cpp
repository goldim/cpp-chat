#include "message.hpp"

using namespace boost::posix_time;

Message::Message(std::string str) 
{
}


Message::Message(IDClient &_id, std::string _text, time_t _time) 
{
    id       = _id;
    text     = _text;
    sendTime = _time;
}

IDClient Message::get_id() const
{
    return id;
}

std::ostream &operator <<(std::ostream& out, const Message& msg) 
{
    ptime time = from_time_t(msg.sendTime);
    time_facet *facet = new time_facet("%H:%M:%S");
    out.imbue(std::locale(std::locale::classic(), facet));
    out << "[" << time << "] " << "<" << msg.id << "> " << msg.text;
    return out;
}