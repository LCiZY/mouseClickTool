//#include<thread>
//#include<process.h>
#include<QDebug>
#include "mouse_automatic.h"
#include <QApplication>
#include<mythread.h>






int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    static_assert(false, "error!");
    mouse_automatic w;
    w.show();


    return a.exec();
}



