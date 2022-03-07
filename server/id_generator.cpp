#include "id_generator.hpp"

IDGenerator::IDGenerator() 
{
    counter = 0;
}

unsigned int IDGenerator::createId() 
{
    counter++;
    return counter;
}

IDGenerator *IDGenerator::Instance() 
{
    if (_instance == nullptr)
    {
        _instance = new IDGenerator;
    }
    return _instance;
}

IDGenerator *IDGenerator::_instance = nullptr;
