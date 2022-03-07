#include "interface.cpp"
#include "server.hpp"

int main(int argc, char** argv)
{    
    Server *General = new Server("config.ini");
    General->start();
    return 0;
}






