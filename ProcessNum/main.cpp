#include "ProcessNumWindow.h"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	StartWorkerSpec startType;
	TextWorkerSpec textType;
	ProcessNumWindow w(&startType, &textType);
    w.show();
    return a.exec();
}
