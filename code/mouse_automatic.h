#ifndef MOUSE_AUTOMATIC_H
#define MOUSE_AUTOMATIC_H

#include <QMainWindow>
#include<windows.h>
#include<QSoundEffect>
#include<mythread.h>
#include<qdoublevalid.h>
#include<QIntValidator>
#include<QPixmap>
#include <QCloseEvent>
#include<QGraphicsDropShadowEffect>

namespace Ui {
class mouse_automatic;
}

class mouse_automatic : public QMainWindow
{
    Q_OBJECT

public:

    explicit mouse_automatic(QWidget *parent = 0);
    ~mouse_automatic();
    friend LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

    void Sleep(int msec);
signals:
    void end_loading();

private slots:
void clickevent();
void recordAction();
void pleasewait();
void recordAction_direction();
void input_hide(QString);
void end_thread();
void accept(QString);
void mouseleftpress();



void on_pushButton_2_clicked();

protected:
void closeEvent(QCloseEvent *event);

private:
    Ui::mouse_automatic *ui;
    QSoundEffect endingmusic;
    qdoublevalid *valid;
    QIntValidator *int_valid;
    MyTherad t;
    QPixmap back;

};







#endif // MOUSE_AUTOMATIC_H
