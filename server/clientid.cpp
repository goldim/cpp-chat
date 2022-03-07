#include "clientid.hpp"

IDClient::IDClient(int _id, std::string _login)
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