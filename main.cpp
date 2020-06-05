#include "deletenewlines.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DeleteNewlines w;
    w.show();
    return a.exec();
}
