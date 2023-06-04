#ifndef DWINDOW_H
#define DWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>

class dwindow: public QDialog
{
    Q_OBJECT
public:
       explicit dwindow(QWidget *parent = nullptr);
private:
       QLineEdit *passportLineEdit;
       QPushButton *confirmButton;
signals:
       void deleteConfirmed(const QString&);
private slots:
       void confirmDelete();
};

#endif // DWINDOW_H
