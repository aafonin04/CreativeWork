#ifndef CLOSE_BILL_H
#define CLOSE_BILL_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>

class close_bill: public QDialog
{
    Q_OBJECT
public:
     explicit close_bill(QWidget *parent=nullptr);
protected:
    QLineEdit* BillNum;
    QPushButton* closebill_confirmed_btn;
signals:
    void closebill_confirmed(const QString&);
private slots:
    void ConfirmClosebill();
};

#endif // CLOSE_BILL_H
