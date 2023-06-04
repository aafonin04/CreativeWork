#include "plusemoney.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>

plusemoney::plusemoney(QWidget *parent)
    :QDialog (parent)
{
    setWindowTitle("Пополнение счёта");
    setModal(true);
    resize(450, 150);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    BillNum=new QLineEdit(this);
    Summ=new QLineEdit(this);
    Valute= new QComboBox(this);
    Valute->addItem("RUB");
    Valute->addItem("USD");
    Valute->addItem("CNY");
    plusemoney_confirmed_btn=new QPushButton("Нажмите для подтверждения", this);
    connect(plusemoney_confirmed_btn, &QPushButton::clicked, this, &plusemoney::plusemoney_Confirm);
    QLabel* label1 = new QLabel("№ счёта", this);
    QLabel* label2 = new QLabel("Сумма пополнения", this);
    QLabel* label3 = new QLabel("Валюта пополнения", this);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, BillNum);
    layout2->addRow(label2, Summ);
    layout2->addRow(label3,  Valute);
    layout2->addWidget(plusemoney_confirmed_btn);
    setLayout(layout2);
}

void plusemoney::plusemoney_Confirm()
{
     emit plusemoney_Confirmed(BillNum->text(), Summ->text(),Valute->currentText());
     BillNum->clear();
     Summ->clear();
}
