#include "mythread.h"
#include<windows.h>
#include<QDebug>
#include<QApplication>


volatile bool close;

MyTherad::MyTherad()
{
 exit_sign=false;
}

HHOOK g_hKebord;

LRESULT CALLBACK g_hKebordProc(int nCode, WPARAM wParam, LPARAM lParam)
{

    if (nCode >= 0)
    {
        PKBDLLHOOKSTRUCT pmll = (PKBDLLHOOKSTRUCT)lParam;
        //PMSLLHOOKSTRUCT
        if (pmll->vkCode==VK_ESCAPE)
        {
           // w.close();
           // qApp->exec();
            PostQuitMessage(0);
            Sleep(100);
            qDebug()<<"Apilication exit!";


            //QString lu1="第"; QString lu2=QString::number(count_click); QString lu3="次录制成功";QString lu=lu1+lu2+lu3;
            //mouse_automatic::ui->textEdit->setText(lu);
        }




    }

    return CallNextHookEx(g_hKebord, nCode, wParam, lParam);
}



void mousepro1() {

    MSG msg;
    g_hKebord = SetWindowsHookEx(WH_KEYBOARD_LL, g_hKebordProc, GetModuleHandle(NULL), 0);



    while (GetMessage(&msg, NULL, 0, 0) != 0)
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }



    UnhookWindowsHookEx(g_hKebord);
    return;

}

void MyTherad::setsign(bool a)
{
    exit_sign=a;
}

void MyTherad::run(){

    qDebug()<<"MyThreadRun!";
    mousepro1();
     exit_sign=true;
    emit closesignal(QString("Thread close."));
}

void MyTherad::startThread(){
    run();
}
