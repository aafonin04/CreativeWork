#include "dwindow.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QLabel>

dwindow::dwindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Удаление клиента");
    setModal(true);
    resize(400, 100);
    QIcon windowIcon(":/delbd.png");
    setWindowIcon(windowIcon);
    passportLineEdit=new QLineEdit(this);
    confirmButton = new QPushButton("Нажмите для подтверждения", this);
    connect(confirmButton, &QPushButton::clicked, this, &dwindow::confirmDelete);
    QLabel* label = new QLabel("№ паспорта клиента", this);
    label->setAlignment(Qt::AlignCenter);
    QFormLayout* layout1 = new QFormLayout();
    layout1->addRow(label, passportLineEdit);
    layout1->addWidget(confirmButton);
    setLayout(layout1);
}

void dwindow::confirmDelete(){
    emit deleteConfirmed(passportLineEdit->text());
    passportLineEdit->clear();
}
