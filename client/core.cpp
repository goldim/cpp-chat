#include "core.hpp"
#include "ioc_container.hpp"

using namespace boost::property_tree;

Client::Client(std::string _ip, int _port, std::string _login) 
{
    const char *filename = "config.ini";
    ini_parser::read_ini(filename, cfg);
    cfg.put("options.ip", _ip);
    cfg.put("options.port", _port);
    ini_parser::write_ini(filename, cfg);
    bufferSize = cfg.get<int>("options.buffer_size");
    serializer = IOCContainer::Instance()->resolve<ISerializer<Message>>();
    idserializer = IOCContainer::Instance()->resolve<ISerializer<IDClient>>();
    sock = IOCContainer::Instance()->resolve<IClientSocket>();
    login = _login;
    buffer = new char[bufferSize];
}

Client::~Client() 
{
    delete buffer;
    delete id;
    sock->stop();
}

void Client::start() throw(SocketException)
{
    sock->connect();
    IDClient client(login);
    Message m(client, "");
    sock->send(serializer->serialize(m), bufferSize);
    sock->receive(buffer, bufferSize);
    id = idserializer->deserialize(std::string(buffer));
}

void Client::send_msg(std::string text)
{
    Message m(*id, text);
    sock->send(serializer->serialize(m), bufferSize);
}

std::string Client::receive_msg()
{
    sock->receive(buffer, bufferSize);
    std::string sMsg(buffer);
    Message *m;
    m = serializer->deserialize(sMsg);
    std::ostringstream msg("");
    msg << *m << '\n';
    return msg.str();
}


