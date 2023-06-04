#ifndef TABLEBILLS_H
#define TABLEBILLS_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include "add_bill.h"
#include "tablewindow.h"
#include "valutes.h"
#include "givemoney.h"
#include "off_bill.h"
#include "close_bill.h"
#include "plusemoney.h"

class tablebills: public QMainWindow
{
    Q_OBJECT
public:
    explicit tablebills(QWidget *parent=nullptr);
    void setTableBillsData(const QList<QStringList>& billsdata);
private:
    QTableWidget* tableBillsWidget;
    QPushButton* add_bill_btn;
    QPushButton* valute_btn;
    QPushButton* givemoney_btn;
    QPushButton* offBills_btn;
    QPushButton* close_bill_btn;
    QPushButton* plus_bill_btn;
    add_bill* add_window_bills;
    Valutes* cours;
    givemoney* givemoney_window;
    off_bill* off_bill_window;
    close_bill* closebillWindow;
    plusemoney* plusemoney_window;

private slots:
    void on_givemoney_window_clicked();
    void on_valute_btn_clicked();
    void on_add_bill_btn_clicked();
    void on_off_bill_window_clicked();
    void close_bill_btn_clicked();
    void on_plus_bill_btn_clicked();
    void give_money_from_bills(const QString&, const QString&,const QString&,const QString&);
    void plus_money_on_bills(const QString&, const QString&,const QString&);
    void add_bills(const QString&,const QString&);
    void off_bill_methode(const QString&,const QString&);
    void Close_Bill(const QString&Num);

};

#endif // TABLEBILLS_H
