#ifndef MYTHREAD_H
#define MYTHREAD_H

#include<QThread>
#include<QString>

class MyTherad : public QThread
{
    Q_OBJECT
public:
    MyTherad();
    void run() override;
    void startThread();
    void setsign(bool);
    volatile bool exit_sign;
signals:
    void closesignal(QString s);

};


#endif // MYTHREAD_H
