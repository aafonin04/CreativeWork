#ifndef OFF_BILL_H
#define OFF_BILL_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class off_bill: public QDialog
{
    Q_OBJECT
public:
    explicit off_bill(QWidget *parent = nullptr);
private:
    QLineEdit* BillNum;
    QLineEdit* code_word;
    QPushButton* off_confirm_btn;
signals:
    void bill_OffConfirmed(const QString&, const QString&);
private slots:
    void bill_ConfirmOff();
};

#endif // OFF_BILL_H
