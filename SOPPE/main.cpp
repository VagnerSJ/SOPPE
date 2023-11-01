#include "mainsoppe.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSoppe w;
    w.show();
    return a.exec();
}
