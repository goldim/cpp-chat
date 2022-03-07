#include "graphic_interface.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Periphery *w = new Periphery;
    w->turn_on();
    return app.exec();
}



