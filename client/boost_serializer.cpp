#include "boost_serializer.hpp"

template <class A>
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
        template<class Archive>
        void serialize(Archive& ar, Message& m, unsigned int v) 
        {
            ar & m.sendTime;
            ar & m.id;
            ar & m.text;
        }
        
        template<class Archive>
        void serialize(Archive& ar, IDClient& id, unsigned int v) 
        {
            ar & id.id;
            ar & id.login;
        }
    }
}