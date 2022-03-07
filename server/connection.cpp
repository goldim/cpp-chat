#include "connection.hpp"
#include "boost_serializer.cpp"

Connection::Connection()
{
    serializer = IOCContainer::Instance()->resolve<ISerializer<Message>>();
    sock = nullptr;
}

Connection::~Connection()
{
    delete buffer;
    delete sock;
}

void Connection::init(IClientSocket *csock, int size)
{
    buffer = new char[size];
    sizeBuffer = size;
    sock = csock;
    Message *msg = receive();
    id = IDClient(IDGenerator::Instance()->createId(), msg->get_id().login);
    sock->send(IOCContainer::Instance()->resolve<ISerializer<IDClient>>()->serialize(id), sizeBuffer);
    delete msg;
}

/*
 * Прервать соеднинение
 */
void Connection::stop()
{
    sock->stop();
}

/**
 * Получить сообщение  
 * @return IMessage* Возвращает сообщение или 0(NULL) в случае разрыва соединения
 */
Message *Connection::receive() 
{
    Message *msg = nullptr;
    
    if (sock->receive(buffer, sizeBuffer)) 
    {    
        msg = serializer->deserialize(std::string(buffer));
    }
    return msg;
}

void Connection::transmit(Message &msg) 
{
    sock->send(serializer->serialize(msg), sizeBuffer);
}

std::string Connection::client_info() const
{
    return id.ToString() + " with ip " + sock->info();
}