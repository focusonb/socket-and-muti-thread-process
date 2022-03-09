#include "ProcessNumWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	ProcessNumWindow w;
    w.show();
    return a.exec();
}
