#include "off_bill.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QDialog>
#include "tablebills.h"

off_bill::off_bill(QWidget *parent)
    :QDialog(parent)
{
    setWindowTitle("Обнуление счёта");
    setModal(true);
    resize(450, 100);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    BillNum=new QLineEdit(this);
    code_word=new QLineEdit(this);
    off_confirm_btn=new QPushButton("Нажмите для подтверждения",this);
    connect(off_confirm_btn, &QPushButton::clicked,this,&off_bill::bill_ConfirmOff);
    QLabel* label1 = new QLabel("№ счёта", this);
    QLabel* label2 = new QLabel("Кодовое слово", this);
    label1->setAlignment(Qt::AlignCenter);
    label2->setAlignment(Qt::AlignCenter);
    QFormLayout* layout2 = new QFormLayout();
    layout2->addRow(label1, BillNum);
    layout2->addRow(label2, code_word);
    layout2->addWidget(off_confirm_btn);
    setLayout(layout2);
}

void off_bill::bill_ConfirmOff()
{
    emit bill_OffConfirmed(BillNum->text(),code_word->text());
    BillNum->clear();
    code_word->clear();
}
