#include "ioc_container.hpp"
#include "boost_serializer.cpp"

using namespace boost::property_tree;

std::shared_ptr<Hypodermic::IContainer> IOCContainer::Instance() 
{
    if (_instance == NULL)
    {
        Hypodermic::ContainerBuilder builder;
        boost::property_tree::ptree config;
        ini_parser::read_ini("config.ini", config);
        std::string ip =  config.get<std::string>("options.ip");
        int port       =  config.get<int>("options.port");
        
        builder.registerType<BoostSerializer<Message>>()->as<ISerializer<Message>>();
        builder.registerType<BoostSerializer<IDClient>>()->as<ISerializer<IDClient>>();
        builder.registerInstance<Socket>(std::make_shared<Socket>(ip, port))->as<IClientSocket>();        
        _instance = builder.build();
    }
    return _instance;
}

std::shared_ptr<Hypodermic::IContainer> IOCContainer::_instance = nullptr;