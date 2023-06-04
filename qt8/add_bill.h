#ifndef ADD_BILL_H
#define ADD_BILL_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "tablewindow.h"



class add_bill: public QDialog
{
    Q_OBJECT
public:
    explicit add_bill(QWidget *parent=nullptr);
    void setTableWindow(TableWindow* window_table);
private:
    QPushButton *AddConfirmBtn;
    QLineEdit *FIOLineAdd;
    QLineEdit *PassportLineAdd;
signals:
    void bill_AddConfirmed(const QString&, const QString&);
private slots:
    void bill_ConfirmAdd();
};

#endif // ADD_BILL_H
