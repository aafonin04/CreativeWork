#include "findclient.h"
#include "dwindow.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QLabel>

findclient::findclient(QWidget *parent)
    :QDialog (parent)
{
    setWindowTitle("Поиск клиента");
    setModal(true);
    resize(400, 120);
    QIcon windowIcon(":/bdfind.png");
    setWindowIcon(windowIcon);
    FIOLineFind = new QLineEdit(this);
    PassportLineFind=new QLineEdit(this);
    FConfirmBtn = new QPushButton ("Нажмите для подтверждения",this);
    connect(FConfirmBtn, &QPushButton::clicked, this, &findclient::ConfirmFind);
    QLabel* label4=new QLabel("ФИО клиента", this);
    QLabel* label5=new QLabel("№ паспорта клиента", this);
    QFormLayout* layout3 = new QFormLayout();
    layout3->addRow(label4, FIOLineFind);
    layout3->addRow(label5, PassportLineFind);
    layout3->addWidget(FConfirmBtn);
    setLayout(layout3);
}

void findclient::ConfirmFind(){
    emit FindConfirmed(FIOLineFind->text(),PassportLineFind->text());
    FIOLineFind->clear();
    PassportLineFind->clear();
}
