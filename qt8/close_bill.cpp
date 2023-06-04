#include "close_bill.h"
#include <QHeaderView>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QLabel>

close_bill::close_bill(QWidget *parent)
    :QDialog (parent)
{
    setWindowTitle("Закрытие счета");
    setModal(true);
    resize(450, 100);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    BillNum=new QLineEdit(this);
    closebill_confirmed_btn=new QPushButton("Нажмите для подтверждения", this);
    connect(closebill_confirmed_btn, &QPushButton::clicked, this, &close_bill::ConfirmClosebill);
    QLabel* label1 = new QLabel("№ счёта", this);
    label1->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, BillNum);
    layout2->addWidget(closebill_confirmed_btn);
    setLayout(layout2);
}

void close_bill::ConfirmClosebill()
{
    emit closebill_confirmed(BillNum->text());
    BillNum->clear();
}
