#include "loading.h"
#include "ui_loading.h"

loading::loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loading)
{
    ui->setupUi(this);
    effect = new QGraphicsDropShadowEffect; effect->setBlurRadius(6); effect->setColor(Qt::black);
    effect->setOffset(0,0); //为控件设置阴影效果 this 可以换成Qwidget 的任意派生类



    this->setFixedSize(200,150); //设置form窗口大小 （宽，高）
        background = new QFrame(this);
        background->setStyleSheet("background-color:#fff;border-radius:10px;");
        background->setGeometry(0, 0, 200, 150);//从background上（0，0）位置开始（即为最左上角的点），显示一个200*150的界面（宽200，高150）
        label = new QLabel(background);
        label->setGeometry(0, 10, 200, 150);//设置label从（0，10）位置开始，显示一个200*150的界面（宽200，高150）

        movie = new QMovie("loading.gif");
        movie->setScaledSize(QSize(200,150));
        label->setScaledContents(true);
        label->setMovie(movie);
        movie->start();

        background->setGraphicsEffect(effect);

}

loading::~loading()
{
    delete ui;
    delete background;
        delete label;
        delete movie;
        delete effect;

        }
