#include "givemoney.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

givemoney::givemoney(QWidget *parent)
    :QDialog (parent)
{
    setWindowTitle("Списание средств");
    setModal(true);
    resize(450, 150);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    BillNum=new QLineEdit(this);
    Summ=new QLineEdit(this);
    CodeW=new QLineEdit(this);
    Valute= new QComboBox(this);
    Valute->addItem("RUB");
    Valute->addItem("USD");
    Valute->addItem("CNY");
    givemoney_confirmed_btn=new QPushButton("Нажмите для подтверждения", this);
    connect(givemoney_confirmed_btn, &QPushButton::clicked, this, &givemoney::givemoney_Confirm);
    QLabel* label1 = new QLabel("№ счёта", this);
    QLabel* label2 = new QLabel("Сумма списания", this);
    QLabel* label4=new QLabel("Кодовое слово",this);
    QLabel* label3 = new QLabel("Валюта списания", this);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label4->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, BillNum);
    layout2->addRow(label2, Summ);
    layout2->addRow(label4, CodeW);
    layout2->addRow(label3,  Valute);
    layout2->addWidget(givemoney_confirmed_btn);
    setLayout(layout2);
}

void givemoney::givemoney_Confirm()
{
    emit givemoney_Confirmed(BillNum->text(), Summ->text(),Valute->currentText(), CodeW->text());
}
