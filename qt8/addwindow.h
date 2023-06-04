#ifndef ADDWINDOW_H
#define ADDWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

class addwindow: public QDialog
{
    Q_OBJECT
public:
    explicit addwindow(QWidget *parent=nullptr);
private:
    QPushButton *AddConfirmBtn;
    QLineEdit *FIOLineAdd;
    QLineEdit *PhoneLineAdd;
    QLineEdit *PassportLineAdd;
signals:
    void AddConfirmed(const QString&, const QString&, const QString&);
private slots:
    void ConfirmAdd();
};

#endif // ADDWINDOW_H
