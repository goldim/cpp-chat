#include "json_serializer.hpp"

template <class A>
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
    template<class Archive>
    void serialize(Archive& ar, Message& m, unsigned int v) 
    {
        ar(m.sendTime, m.id, m.text);
    }

    template<class Archive>
    void serialize(Archive& ar, IDClient& id, unsigned int v) 
    {
        ar(id.id, id.login);
    }
}
