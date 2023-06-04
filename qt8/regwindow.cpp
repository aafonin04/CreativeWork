#include "regwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "mainwindow.h"

regwindow::regwindow(QWidget *parent)
    :QDialog(parent)
{
      setWindowTitle("Авторизация");
      setModal(true);
      resize(450, 150);
      loginLineEdit = new QLineEdit(this);
      passwordLineEdit = new QLineEdit(this);
      passwordLineEdit->setEchoMode(QLineEdit::Password);
      registrButton = new QPushButton("Войти", this);
      connect(registrButton, &QPushButton::clicked, this, &regwindow::loginClicked);
      QVBoxLayout *mainLayout = new QVBoxLayout(this);
      QFormLayout *formLayout = new QFormLayout();
      formLayout->addRow("Логин:", loginLineEdit);
      formLayout->addRow("Пароль:", passwordLineEdit);
      mainLayout->addLayout(formLayout);
      mainLayout->addWidget(registrButton);
}

void regwindow::setMainWindow(MainWindow* mainWindow)
{
    this->mainWindow = mainWindow;
}

void regwindow::loginClicked()
{
    QString login = loginLineEdit->text();
    QString password = passwordLineEdit->text();

    // Проверка логина и пароля
    if ((login == "Afonin04" && password == "30082004")||(login=="Bobrikov04"&&password=="01102004")) {
        // Авторизация успешна
        accept();
        if (mainWindow) {
            mainWindow->getClientButton()->setEnabled(true);
            mainWindow->getBillsButton()->setEnabled(true);
            mainWindow->getResultButton()->setEnabled(true);
            loginLineEdit->clear();
            passwordLineEdit->clear();

            close();
        }
    } else {
        // Ошибка авторизации
        loginLineEdit->clear();
        passwordLineEdit->clear();
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    }
}
