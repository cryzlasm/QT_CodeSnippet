#include "widget.h"
#include "ui_widget.h"
#include "CToastLabel.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_pressed()
{
    CToastLabel* pToast = new CToastLabel("Test");
    pToast->popup(this);
}
