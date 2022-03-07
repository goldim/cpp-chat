#ifndef REGISTER_HPP
#define	REGISTER_HPP

//ioc container
#include <Hypodermic/IContainer.h>
#include <Hypodermic/ContainerBuilder.h>
#include <Hypodermic/ActivatingData.h>
#include <Hypodermic/Container.h>
#include <Hypodermic/AutowiredConstructor.h>
#include <Hypodermic/Helpers.h>
#include <Hypodermic/IComponentContext.h>
#include <Hypodermic/NullptrWorkaround.h>
#include <Hypodermic/IComponentContext.h>
// myimplementation
#include "socket.hpp"
#include "storage.hpp"
#include "connection.hpp"
//boost
#include <boost/property_tree/ini_parser.hpp>

/**
 * @brief Singleton, инкапсулирует IOC контейнер
 * @class IOCContainer
 */
class IOCContainer
{
    public:
        /**
         * @brief  Получает экземпляр синглтона
         */
        static std::shared_ptr<Hypodermic::IContainer> Instance();
    private:
        static std::shared_ptr<Hypodermic::IContainer> _instance;
    protected:
        IOCContainer();
};

#endif

