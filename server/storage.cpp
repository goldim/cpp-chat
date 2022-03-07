#include "storage.hpp"
#include <iostream>

void Storage::add(const Message& msg) 
{
    messages.push_back(msg);
}

Message &Storage::select(int index)
{
    return messages[index];
}

int Storage::count() const
{
    return messages.size();
}







