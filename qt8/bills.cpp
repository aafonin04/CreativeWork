#include "bills.h"
#include "ui_bills.h"

Bills::Bills(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bills)
{
    ui->setupUi(this);
}

Bills::~Bills()
{
    delete ui;
}
