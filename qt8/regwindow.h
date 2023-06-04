#ifndef REGWINDOW_H
#define REGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class MainWindow;

class regwindow: public QDialog
{
    Q_OBJECT
public:
    explicit regwindow(QWidget *parent=nullptr);
    void setMainWindow(MainWindow* mainWindow);
private slots:
    void loginClicked();
private:
    QLineEdit *loginLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *registrButton;
    MainWindow* mainWindow;
};

#endif // REGWINDOW_H
