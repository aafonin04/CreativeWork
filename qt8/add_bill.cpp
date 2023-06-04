#include "add_bill.h"

#include <QLabel>
#include<QFormLayout>


add_bill::add_bill(QWidget*parent)
    :QDialog(parent)
{
    setWindowTitle("Открытие нового счёта");
    setModal(true);
    resize(400, 100);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    FIOLineAdd=new QLineEdit(this);
    PassportLineAdd=new QLineEdit(this);
    AddConfirmBtn=new QPushButton("Нажмите для подтверждения", this);
    connect(AddConfirmBtn, &QPushButton::clicked, this, &add_bill::bill_ConfirmAdd);
    QLabel* label1 = new QLabel("ФИО клиента", this);
    QLabel* label3 = new QLabel("№ паспорта клиента", this);
    label1->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, FIOLineAdd);
    layout2->addRow(label3,  PassportLineAdd);
    layout2->addWidget( AddConfirmBtn);
    setLayout(layout2);

}

void add_bill::bill_ConfirmAdd()
{
    emit bill_AddConfirmed(FIOLineAdd->text(),PassportLineAdd->text());
    FIOLineAdd->clear();
    PassportLineAdd->clear();
}



