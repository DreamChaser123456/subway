#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>
Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPushButton *btn=new QPushButton("第一个按钮",this);

}

Widget::~Widget()
{
    delete ui;
}


