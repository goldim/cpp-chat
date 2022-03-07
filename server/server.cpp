#include "server.hpp"
#include <iostream>

using namespace boost::threadpool;
using namespace boost::property_tree;

Server::Server(std::string configPath)
{
    ini_parser::read_ini(configPath.c_str(), cfg);
    int maxCount        = cfg.get<int>("options.connection_count");
    std::string logpath = cfg.get<std::string>("options.log_file_name");
    sock = IOCContainer::Instance()->resolve<IServerSocket>();
    store = IOCContainer::Instance()->resolve<IStorage>();
    tpool = std::make_shared<pool>(maxCount);
    init_log(logpath);
}

void Server::start()
try
{   
    sock->bind();
    sock->listen(); 
    while (auto client = sock->accept())
        add(client);//добавить новое соединение
}
catch(SocketException &e)
{
    log->error(e.what());
}

/* остановить прием новых соединений, прием сообщений*/
void Server::stop()
{
    sock->stop();
    for (const auto &it: connections) it->stop();
}

void Server::send_all(Message &msg)
{
    for (const auto &it: connections) it->transmit(msg);
}

void Server::service(std::shared_ptr<IConnection> con, Server *server)
{    
    while (Message *msg = con->receive())
    {
        server->mtx.lock();
        server->store->add(*msg);//сохранить в хранилище
        std::cout << *msg << std::endl;//вывод на консоль присланного сообщения
        server->send_all(*msg);//отослать всем присланное сообщение
        server->mtx.unlock();
        delete msg;
    }
    server->mtx.lock();
    server->log->info("User " + con->client_info() + " disconnected");//записать в журнал, что пользовать ушел в оффлайн
    server->connections.remove(con);
    server->mtx.unlock();
}

void Server::add(IClientSocket *csock) 
{
    int size =  cfg.get<int>("options.buffer_size");
    auto con = IOCContainer::Instance()->resolve<IConnection>(); 
    mtx.lock();
    connections.push_back(con);
    con->init(csock, size);//установить соединение
    for (int i = 0; i < store->count(); ++i)
        con->transmit(store->select(i));//передать ему предыдущие сообщения
    log->info("User " + con->client_info() + " connected");//записать в журнал, что пользовать подключился
    mtx.unlock();
    tpool->schedule(std::bind(service, con, this));//обмен данными с клиентом в отд потоке
}

void Server::init_log(std::string path) 
{
    log4cpp::Appender *appender = new log4cpp::FileAppender("default", path);
    appender->setLayout(new log4cpp::BasicLayout());
    log4cpp::Category &root = log4cpp::Category::getInstance(std::string("root"));
    root.setPriority(log4cpp::Priority::INFO);
    root.addAppender(appender);
    log = &root;
}
