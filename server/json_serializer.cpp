/**
 * @brief сериализация через библиотеку cereal
 * 
 * В данном файле описывается класс сериализатор.
 * Для каждого сериализируемого класса описывается
 * функция serialize
 * @author Золотов Д. <goldim1993@mail.ru>
 */

#include "json_serializer.hpp"

/**
 * @brief класс-шаблон, сериализатор, реализующий операции сериализации через библиотеку cereal
 * 
 * Представлен как шаблон класса, где аргументом шаблона является объект,
 * подлежащий сериализации. Объект данного класса сериализуется в JSON строку.
 * @class JSONSerializer наследует интерфейс ISerializer
 * @tparam A сериализируемый класс
 */
template <typename A>
class JSONSerializer: public ISerializer<A>
{
    public:
        std::string serialize(A obj)
        {
            std::stringstream result;
            {
                cereal::JSONOutputArchive oa(result); // Create an output archive
                oa(obj);
            }
            return result.str();
        }
        
        A* deserialize(std::string input)
        {
            A* o = new A;
            std::stringstream result(input);
            {
                cereal::JSONInputArchive ia(result); // Create an output archive
                ia(*o);
            }
            return o;
        }
};

namespace cereal 
{ 
    /**
    * @brief служит для перечисления свойств класса Message,
    * подлежащего сериализации
    * 
    * Сериализирует уникальный идентификатор отправителя сообщения, 
    * время отправки и тело сообщения 
    * @param[out] ar объект архива boost
    * @param[in] m объект класса Message, подлежащий сериализации
    * @param[in] v версия сериализуемого класса
    * при изменении структуры класса ему присваивается другой номер версии
    * @tparam Archive архив, инкапсулирует способ сериализации
    */
    template<class Archive>
    void serialize(Archive& ar, Message& m, unsigned int v) 
    {
        ar(m.sendTime, m.id, m.text);
    }
    /**
    * @brief служит для перечисления свойств класса IDClient,
    * подлежащего сериализации
    * 
    * Сериализирует идентификатор клиента и его логин
    * @param[out] ar объект архива boost
    * @param[in] m объект класса IDClient, подлежащий сериализации
    * @param[in] v версия сериализуемого класса
    * при изменении структуры класса ему присваивается другой номер версии
    * @tparam Archive архив, инкапсулирует способ сериализации
    */
    template<class Archive>
    void serialize(Archive& ar, IDClient& id, unsigned int v) 
    {
        ar(id.id, id.login);
    }
}
