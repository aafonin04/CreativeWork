#ifndef GIVEMONEY_H
#define GIVEMONEY_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QComboBox>

class givemoney: public QDialog
{
     Q_OBJECT
public:
    explicit givemoney(QWidget *parent=nullptr);
protected:
    QLineEdit* BillNum;
    QLineEdit* Summ;
    QLineEdit* CodeW;
    QComboBox* Valute;
    QPushButton* givemoney_confirmed_btn;
signals:
    void givemoney_Confirmed(const QString&,const QString&,const QString&,const QString&);
private slots:
    void givemoney_Confirm();
};

#endif // GIVEMONEY_H
