#include <QApplication>
#include "Task.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Task w;
    w.show();
    return a.exec();
}
