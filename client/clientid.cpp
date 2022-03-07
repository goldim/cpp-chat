#include "clientid.hpp"

IDClient::IDClient(std::string _login, int _id)
{
    id = _id;
    login = _login;
}

std::ostream &operator <<(std::ostream& out, const IDClient& id) 
{
    out << id.login;
    return out;
}

std::string IDClient::ToString() const
{
    return login;
}