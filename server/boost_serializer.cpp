/**
 * @brief сериализация через библиотеку boost
 * 
 * В данном файле описывается реализация класса сериализатора.
 * Для каждого сериализируемого класса описывается
 * функция serialize
 * @author Золотов Д. <goldim1993@mail.ru>
 */

#include "boost_serializer.hpp"

/**
 * @brief класс-шаблон, сериализатор, реализующий операции сериализации через библиотеку boost
 * 
 * Представлен как шаблон класса, где аргументом шаблона является объект,
 * подлежащий сериализации
 * @class BoostSerializer наследует интерфейс ISerializer
 * @tparam A сериализируемый класс
 */
template <typename A>
class BoostSerializer: public ISerializer<A>
{
    public:
        std::string serialize(A obj)
        {
            std::stringstream result;
            boost::archive::text_oarchive ao(result);
            ao << obj;       
            return result.str();
        }

        A* deserialize(std::string input)
        {
            A* o = new A;
            std::stringstream iss(input);
            boost::archive::text_iarchive ia(iss);
            ia >> *o;
            return o;
        }
};

namespace boost 
{ 
    namespace serialization 
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
            ar & m.sendTime;
            ar & m.id;
            ar & m.text;
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
            ar & id.id;
            ar & id.login;
        }
    }
}