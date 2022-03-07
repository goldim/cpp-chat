#ifndef ID_ENUMERATOR_HPP
#define	ID_ENUMERATOR_HPP

/**
 * @brief Singleton, инкапсулирует IOC контейнер
 * @class IOCContainer
 */
class IDGenerator
{
    public:
        /**
         * @brief  Получает экземпляр синглтона
         */
        static IDGenerator *Instance();
        unsigned int createId();
    private:
        static IDGenerator *_instance;
        unsigned int counter;
    protected:
        IDGenerator();
};

#endif	/* ID_ENUMERATOR_HPP */

