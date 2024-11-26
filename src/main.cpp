#include "widget.h"
#include <QApplication>
#include <QDate>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Widget w;
    // w.show();
    QList<QString> test({QString("Hello"), QString("World")});
    QString str = "Hello, World!";
    QMap <int, QString> map;
    QDate date = QDate::currentDate();
    QVector <int> vector;
    vector.append(1);
    vector.append(2);
    vector.append(3);
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");
    return a.exec();
}
