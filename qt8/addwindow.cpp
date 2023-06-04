#include "addwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>

addwindow::addwindow(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("Добавление клиента");
    setModal(true);
    resize(450, 150);
    QIcon windowIcon(":/addbd.png");
    setWindowIcon(windowIcon);
    FIOLineAdd=new QLineEdit(this);
    PhoneLineAdd=new QLineEdit(this);
    PassportLineAdd=new QLineEdit(this);
    AddConfirmBtn=new QPushButton("Нажмите для подтверждения", this);
    connect(AddConfirmBtn, &QPushButton::clicked, this, &addwindow::ConfirmAdd);
    QLabel* label1 = new QLabel("ФИО клиента", this);
    QLabel* label2 = new QLabel("№ телефона клиента", this);
    QLabel* label3 = new QLabel("№ паспорта клиента", this);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    label3->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, FIOLineAdd);
    layout2->addRow(label2, PhoneLineAdd);
    layout2->addRow(label3,  PassportLineAdd);
    layout2->addWidget( AddConfirmBtn);
    setLayout(layout2);
}

void addwindow::ConfirmAdd(){
    emit AddConfirmed(FIOLineAdd->text(), PhoneLineAdd->text(), PassportLineAdd->text());
    FIOLineAdd->clear();
    PhoneLineAdd->clear();
    PassportLineAdd->clear();
}
