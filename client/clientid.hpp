#ifndef CLIENTID_HPP
#define	CLIENTID_HPP

#include <string>

class IDClient
{
    public:
        unsigned id;
        std::string login;
        friend std::ostream &operator<<(std::ostream& out, const IDClient &id);
        IDClient(std::string _login = "", int _id = 0);
        std::string ToString() const;
};

#endif	/* CLIENTID_HPP */

