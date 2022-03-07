#ifndef STORAGE_HPP
#define	STORAGE_HPP

#include <deque>
#include "interface.cpp"
#include "message.hpp"

/**
 * В данном случае способ хранения реализован через двустороннюю очередь
 * @class Storage
 */
class Storage: public IStorage
{
        std::deque<Message> messages;
    public:
        Storage(){};
        void add(const Message& msg);
        Message& select(int index);
        int count() const;
};


#endif	/* STORAGE_HPP */

