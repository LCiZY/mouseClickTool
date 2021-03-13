#include "mouse_automatic.h"
#include "ui_mouse_automatic.h"
#include<iostream>
#include<windows.h>
#include<conio.h>
#include <stdio.h>
#include <QTime>
#include <QThread>
#include<loading.h>
#include<QFile>
#include"QFileDialog"
#include<QMessageBox>
#include<mythread.h>
#include<QDebug>
#include<QKeyEvent>

extern bool close;

mouse_automatic::mouse_automatic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mouse_automatic)
{
       ui->setupUi(this);
       ui->statusBar->hide();
       QFile qssfile(":/style/style.qss");
       qssfile.open(QFile::ReadOnly);
       QString qss;
       qss = qssfile.readAll();
        qssfile.close();

        back.load(":/new/icon/back.jpeg");

      //  ui->label_background->setPixmap(back);

    valid=new qdoublevalid(0); valid->setNotation(QDoubleValidator::StandardNotation); valid->setRange(0,32.0,3);   //设置top是32.0和bottom是0.01（但是仍然可以输入0） ，最后一个小数表示有3位小数
    int_valid=new QIntValidator; int_valid->setRange(1,65536);
   // t.start();
     connect(ui->pushButton,SIGNAL(clicked()), this, SLOT(clickevent()));
     connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(recordAction()));
     connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(recordAction_direction()));
     connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(end_thread()));
     connect(ui->pushButton_5,SIGNAL(clicked()), this, SLOT(mouseleftpress()));
     connect(ui->comboBox,SIGNAL(currentTextChanged(QString)),this,SLOT(input_hide(QString)));
     QObject::connect(&t, SIGNAL(closesignal(QString)), this, SLOT(accept(QString)));

     ui->textEdit->setReadOnly(true); ui->lineEdit->setValidator(int_valid);
     ui->lineEdit_2->setValidator(valid);   //设置时间的有效值是0.001~20秒

     /*
     QGraphicsDropShadowEffect* effect;
     effect = new QGraphicsDropShadowEffect; effect->setBlurRadius(15); effect->setColor(Qt::black);
     effect->setOffset(0,0); //为控件设置阴影效果 this 可以换成Qwidget 的任意派生类
     ui->pushButton->setGraphicsEffect(effect);*/

     endingmusic.setSource(QUrl::fromLocalFile("complete.wav"));
     endingmusic.setVolume(0.8f);

      this->setWindowIcon(QIcon(":/logo/icon.jpg"));
      this->setStyleSheet(qss);
    this->setWindowTitle("Mouse AUTO");

}

void mouse_automatic::accept(QString S){
    qDebug()<<S;
   // qApp->exit(0);  //退出程序
}


struct point{

    int x;
    int y;

};
static QList<point> record;

mouse_automatic::~mouse_automatic()
{
    delete ui;

}

void mouse_automatic::pleasewait()
{

    loading *l=new loading;
    //l->path=QFileDialog::getOpenFileName(this,tr("选择GIF文件"),".",tr("GIF 文件(*.gif)"));
    l->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        l->setWindowModality(Qt::ApplicationModal); ui->textEdit->append("请等待...5s 后开始");
        l->show();Sleep(5000);l->close();emit(end_loading());
       // QMessageBox::about(this,tr("提示"),tr("无法连接到服务器，请检查网络连接后再试！"));

}


void mouse_automatic::Sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MouseMove(point p)
{
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度
        double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度
        double fx = p.x * (65535.0f / fScreenWidth);
        double fy = p.y * (65535.0f / fScreenHeight);
        INPUT  Input = { 0 };
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
        Input.mi.dx = fx;
        Input.mi.dy = fy;
        SendInput(1, &Input, sizeof(INPUT));
}

void MouseLeftDown()//鼠标左键按下
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));

}

void MouseLeftUp()//鼠标左键放开
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));

}

int translateKeyCode(int key);
HHOOK g_hMouse;
int count=0;
int exicsign=1;
char k;


void mouse_automatic::clickevent()
{


    if(ui->lineEdit_2->text().isEmpty()||ui->lineEdit_2->text().isNull()) {
        QMessageBox::about(this,tr("警告"),tr("请输入点击的间隔时间！")); return;
    }
    if(ui->lineEdit_2->text().toDouble()==0.0) {
        QMessageBox::about(this,tr("警告"),tr("【间隔时间】输入错误！")); return;
    }
    if(ui->checkBox->isChecked()){this->showMinimized(); }

    t.start();  t.setsign(false);   //开始键盘监测线程  ,同时初始化退出标志

    QString fangsh=ui->comboBox_2->currentText();
    std::string laa=fangsh.toStdString();
    const char* flag1122=laa.c_str();


    loading *l=new loading;
    l->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        l->setWindowModality(Qt::ApplicationModal);
        l->show();Sleep(5000);l->close();       //loading 界面

if(strcmp(flag1122,"在同一位置点击")==0)
{
    QString cishu=ui->lineEdit->text();
    int m=cishu.toInt();
    double shijian=ui->lineEdit_2->text().toDouble()*1000;
    double n=shijian;


             QString fangshi=ui->comboBox->currentText();
             std::string la=fangshi.toStdString();
             const char* flag112=la.c_str();

     if(strcmp(flag112,"有限次点击")==0)
    {
         if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isNull()){
              QMessageBox::about(this,tr("警告"),tr("请输入点击次数！")); return;
         }

         QString l1="第";
         QString l2="次点击";
         for(int i=0;i<m;i++)
         {
             QString ci=QString::number(i+1);            
             QString l3=l1+ci+l2;
             std::string l4=l3.toStdString();
             const char* cc=l4.c_str();
             if(t.exit_sign==true) {qDebug()<<"Esc press.";break;}
            MouseLeftDown(); MouseLeftUp();
            ui->textEdit->append(cc);
            Sleep(n);

          }
     }
     else {

                    int j=0;
                    QString l1="第";
                    QString l2="次点击";
                    while(1)
                     {
                         ++j;
                         QString ci=QString::number(j);
                         QString l3=l1+ci+l2;
                         std::string l4=l3.toStdString();
                         const char* cc=l4.c_str();
                         ui->textEdit->append(cc);
                         if(t.exit_sign==true) {qDebug()<<"Esc press.";break;}
                         MouseLeftDown(); MouseLeftUp();
                         Sleep(n);
                      }

           }

}
else    //录制动作点击
{
        QString cishu=ui->lineEdit->text();
        int m=cishu.toInt();
        QString shijian=ui->lineEdit_2->text();
        double n=shijian.toDouble();
        n=n*1000;


                 QString fangshi=ui->comboBox->currentText();
                 std::string la=fangshi.toStdString();
                 const char* flag112=la.c_str();

        if(strcmp(flag112,"有限次点击")==0)
        {
            if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isNull()){
                 QMessageBox::about(this,tr("警告"),tr("请输入点击次数！")); return;
            }

            for(int ii=0;ii<m;ii++)
            {
                QString ci=QString::number(ii+1);
               QString l1="第";
               QString l2="组点击";
               QString l3=l1+ci+l2;
              std::string l4=l3.toStdString();
              const char* cc=l4.c_str();
             ui->textEdit->append(cc);
             if(t.exit_sign==true) {break;}

                for(int jj=0;jj<record.size();jj++)
                {
                    if(t.exit_sign==true) { qDebug()<<"Esc press.";break;}
                    MouseMove(record[jj]);MouseLeftDown();MouseLeftUp();Sleep(n);             
                }

            }


        }
        else   //无限组点击
        {
            int iii=0;
            QString l1="第";
            QString l2="组点击";
            while(exicsign)
            {   iii++;

                if(t.exit_sign==true) {qDebug()<<"Esc press.";break;}
                QString ci=QString::number(iii);              
                QString l3=l1+ci+l2;
                std::string l4=l3.toStdString();
                const char* cc=l4.c_str();
                ui->textEdit->append(cc);
                for(int jj=0;jj<record.size();jj++)
                {
                    if(t.exit_sign==true) {qDebug()<<"Esc press.";break;}
                    MouseMove(record[jj]);MouseLeftDown();MouseLeftUp();Sleep(n);
                }


            }

        }


}
ui->textEdit->append(QString("操作完成。"));
t.terminate();
endingmusic.play();
}

static int count_click=0;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        PMSLLHOOKSTRUCT pmll = (PMSLLHOOKSTRUCT)lParam;

        if (wParam== WM_RBUTTONDOWN)
        {
            count_click++;
            point a; a.x=pmll->pt.x; a.y=pmll->pt.y;
            record.push_back(a);
        }

        if (wParam == WM_MBUTTONDOWN)
        {
           // PostThreadMessageA(GetCurrentThreadId,WM_QUIT,0,0);
            PostQuitMessage(0);
        }


    }

    return CallNextHookEx(g_hMouse, nCode, wParam, lParam);
}


void mouse_automatic::recordAction()
{
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_3->setText("正在录制...");
     MSG msg;
     g_hMouse = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, GetModuleHandle(NULL), 0);

 mouse_automatic::ui->textEdit->append("开始录制");

    while (GetMessage(&msg, NULL, 0, 0)!=0)
    {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


      mouse_automatic::ui->textEdit->append("结束录制");
        UnhookWindowsHookEx(g_hMouse);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_3->setText("点击录制动作");
}

void mouse_automatic::recordAction_direction()
{

      QMessageBox::about(this,tr("说明"),tr("①将鼠标移动到需要鼠标左键点击的位置后\n"
                                          "按右键依次记录鼠标的位置；按鼠标滚轮键结束录制"
                                          "\n②运行过程中按Esc退出程序"));

}



void mouse_automatic::end_thread()
{

    this->close();

}

void mouse_automatic::input_hide(QString s)
{
    std::string s1=s.toStdString();
    const char* s2=s1.c_str();
    if(strcmp(s2,"有限次点击")==0){
        ui->label->show();ui->lineEdit->show();
    }
    if(strcmp(s2,"无限次点击")==0){
        ui->label->hide();ui->lineEdit->hide();
    }
}

int translateKeyCode(int key)   //按键转换值函数
{
    int k = key;
    bool legal = true;
    if(k >= Qt::Key_0 && k <= Qt::Key_9)
    {
    }
    else if(k >= Qt::Key_A && k <= Qt::Key_Z)
    {
    }
    else if(k >= Qt::Key_F1 && k <= Qt::Key_F24)
    {
        k &= 0x000000ff;
        k += 0x40;
    }
    else if(k == Qt::Key_Tab)
    {
        k = 0x09;
    }
    else if(k == Qt::Key_Backspace)
    {
        k = 0x08;
    }
    else if(k == Qt::Key_Return)
    {
        k = 0x0d;
    }
    else if(k <= Qt::Key_Down && k >= Qt::Key_Left)
    {
        int off = k - Qt::Key_Left;
        k = 0x25 + off;
    }
    else if(k == Qt::Key_Shift)
    {
        k = 0x10;
    }
    else if(k == Qt::Key_Control)
    {
        k = 0x11;
    }
    else if(k == Qt::Key_Alt)
    {
        k = 0x12;
    }
    else if(k == Qt::Key_Meta)
    {
        k = 0x5b;
    }
    else if(k == Qt::Key_Insert)
    {
        k = 0x2d;
    }
    else if(k == Qt::Key_Delete)
    {
        k = 0x2e;
    }
    else if(k == Qt::Key_Home)
    {
        k = 0x24;
    }
    else if(k == Qt::Key_End)
    {
        k = 0x23;
    }
    else if(k == Qt::Key_PageUp)
    {
        k = 0x21;
    }
    else if(k == Qt::Key_Down)
    {
        k = 0x22;
    }
    else if(k == Qt::Key_CapsLock)
    {
        k = 0x14;
    }
    else if(k == Qt::Key_NumLock)
    {
        k = 0x90;
    }
    else if(k == Qt::Key_Space)
    {
        k = 0x20;
    }
    else
        legal = false;

    if(!legal)
        return 0;
    return k;
}


void pausemode()
{


      for(int i=0;i<20;i++)
        keybd_event(Qt::Key_C,translateKeyCode(Qt::Key_C),KEYEVENTF_EXTENDEDKEY, 0);  //模拟输入按键C

        Sleep(500);

       for(int i=0;i<40;i++)
         keybd_event(Qt::Key_V,translateKeyCode(Qt::Key_V),KEYEVENTF_EXTENDEDKEY, 0);  //模拟输入按键V





}


void mouse_automatic::mouseleftpress()
{
    loading *l1=new loading;
    l1->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        l1->setWindowModality(Qt::ApplicationModal);
        l1->show();Sleep(3000);l1->close();
        int count=0;
        while(true)

        {

            count++;
            if(count%10==0) pausemode();
            if(count%10==0)  {
                MouseLeftUp();
                Sleep(500);
                keybd_event(Qt::Key_L,translateKeyCode(Qt::Key_L),KEYEVENTF_EXTENDEDKEY, 0);
                Sleep(500);
                 keybd_event(Qt::Key_L,translateKeyCode(Qt::Key_L),KEYEVENTF_EXTENDEDKEY, 0);
                //模拟输入按键V
            }

         MouseLeftDown();  if(kbhit()) {char k=_getch(); if(k=='a') break; }  //exit
         Sleep(1000);

            qDebug()<<count;

        }

        /*
        QPoint pos;
        pos=QCursor::pos();
        POINT point;
        point.x=pos.x();
        point.y=pos.y();
        HWND H=WindowFromPoint(point);


        //CONSOLE_MOUSE_DOWN

       // PostMessageA(NULL,WM_LBUTTONDOWN,MK_LBUTTON,MAKELONG(point.x,point.y));
      //  PostMessageA(H,WM_LBUTTONUP,MK_LBUTTON,MAKELONG(point.x,point.y));
        */
      //  keybd_event(Qt::Key_J,translateKeyCode(Qt::Key_J),KEYEVENTF_EXTENDEDKEY, 0);  //模拟输入按键J



}




void mouse_automatic::closeEvent(QCloseEvent *event)
{
    if(t.exit_sign==false) {t.terminate(); t.wait();}
    qApp->quit();

}










void mouse_automatic::on_pushButton_2_clicked()
{
    if(t.exit_sign==false) {t.terminate(); t.wait();}
    qApp->quit();

}
