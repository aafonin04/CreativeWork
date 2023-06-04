#ifndef CODEWINDOW_H
#define CODEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class TableWindow;

class codewindow: public QDialog
{
    Q_OBJECT
public:
    explicit codewindow(QWidget *parent=nullptr);
    void setTableWindow(TableWindow* tableWindow);
private slots:
   void ShowCodeClicked();
private:
    QLineEdit *loginCodeLineEdit;
    QLineEdit *passwordCodeLineEdit;
    QPushButton *CodeButton;
    TableWindow* tableWindow;
};

#endif // CODEWINDOW_H
