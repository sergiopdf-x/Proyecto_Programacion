#include "pacientes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pacientes w;
    w.show();
    return a.exec();
}
