#include "gradebook.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Gradebook w;
    w.show();
    return a.exec();
}
