#ifndef PLUSEMONEY_H
#define PLUSEMONEY_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QComboBox>


class plusemoney: public QDialog
{
     Q_OBJECT
public:
    explicit plusemoney(QWidget *parent=nullptr);
protected:
    QLineEdit* BillNum;
    QLineEdit* Summ;
    QComboBox* Valute;
    QPushButton* plusemoney_confirmed_btn;
signals:
    void plusemoney_Confirmed(const QString&,const QString&,const QString&);
private slots:
    void plusemoney_Confirm();
};

#endif // PLUSEMONEY_H
