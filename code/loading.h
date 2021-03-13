#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include<QTimer>
#include<QLabel>
#include<QMovie>
#include<QFrame>
#include<QGraphicsDropShadowEffect>

namespace Ui {
class loading;
}

class loading : public QWidget
{
    Q_OBJECT

public:
    explicit loading(QWidget *parent = 0);
    ~loading();
    QString path;
private:
         Ui::loading *ui;
        QGraphicsDropShadowEffect* effect;
        QMovie *movie;
        QLabel *label;
        QLabel * tip_label;
        QFrame * background;
        QTimer *timer ;
};

#endif // LOADING_H
