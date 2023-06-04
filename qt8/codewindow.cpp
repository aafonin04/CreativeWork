#include "codewindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "tablewindow.h"

codewindow::codewindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Авторизация");
    setModal(true);
    resize(450, 150);
    loginCodeLineEdit = new QLineEdit(this);
    passwordCodeLineEdit = new QLineEdit(this);
    passwordCodeLineEdit->setEchoMode(QLineEdit::Password);
    CodeButton = new QPushButton("Войти", this);
    connect(CodeButton, &QPushButton::clicked, this, &codewindow::ShowCodeClicked);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Логин:", loginCodeLineEdit);
    formLayout->addRow("Пароль:", passwordCodeLineEdit);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(CodeButton);
}

void codewindow::setTableWindow(TableWindow *tableWindow){
    this->tableWindow=tableWindow;
}
void codewindow::ShowCodeClicked()
{
    QString login = loginCodeLineEdit->text();
    QString password = passwordCodeLineEdit->text();

    // Проверка логина и пароля
    if ((login == "Afonin04" && password == "30082004")||(login=="Bobrikov04"&&password=="01102004")) {
        // Авторизация успешна
        accept();
        if (tableWindow) {
            tableWindow->getTable()->setColumnHidden(3,false);
            loginCodeLineEdit->clear();
            passwordCodeLineEdit->clear();
            close();
        }
    } else {
        // Ошибка авторизации
        loginCodeLineEdit->clear();
        passwordCodeLineEdit->clear();
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    }
}
