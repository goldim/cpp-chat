#ifndef SERVER_HPP
#define	SERVER_HPP

//std
#include <vector>
#include <algorithm>
//boost
#include <boost/threadpool.hpp>
#include <boost/threadpool/pool.hpp>
#include <boost/property_tree/ini_parser.hpp>
// моя реализация чата
#include "message.hpp"
// журнал
#include "log4cpp/Category.hh"
#include "log4cpp/Appender.hh"
#include "log4cpp/FileAppender.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/Layout.hh"
#include "log4cpp/BasicLayout.hh"
#include "log4cpp/Priority.hh"
// ioc
#include "ioc_container.hpp"

/**
 * @class Server
 */
class Server: public IServer
{
    boost::property_tree::ptree cfg;
    std::shared_ptr< IStorage > store;
    std::shared_ptr< IServerSocket > sock;
    std::shared_ptr<boost::threadpool::pool> tpool;
    std::list< std::shared_ptr<IConnection> > connections;
    boost::mutex mtx;  
    log4cpp::Category *log;
public:
    Server(std::string configPath);
    void start();
    void stop();
    void send_all(Message &msg);
private:
    static void service(std::shared_ptr<IConnection> con, Server *server);
    void add(IClientSocket *sock); 
    void init_log(std::string path); 
};

#endif	/* SERVER_HPP */

