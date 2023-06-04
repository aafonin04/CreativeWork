#ifndef TABLEWINDOW_H
#define TABLEWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include "dwindow.h"
#include "addwindow.h"
#include "findclient.h"
#include "regwindow.h"
#include "codewindow.h"

class TableWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit TableWindow(QWidget *parent = nullptr);
    void setTableData(const QList<QStringList>& data);
    QTableWidget* getTable();
private:
    QTableWidget* tableWidget;
    QPushButton* Add_clnt_btn;
    QPushButton* Del_clnt_btn;
    QPushButton* Rand_clnt_btn;
    QPushButton* Find_clnt_btn;
    QPushButton* Code_clnt_btn;
    dwindow* delclWindow;
    addwindow* addclWindow;
    findclient* findclWindow;
    codewindow* codeclWindow;

private slots:
    void Rand_clnt_to_table();
    void on_del_btn_clicked();
    void on_add_btn_clicked();
    void on_find_btn_clicked();
    void on_code_btn_clicked();
    void confirmDeleteClient(const QString&);
    void ConfirmAddClient(const QString&, const QString&, const QString&);
    void confirmFindClient(const QString&, const QString&);
};

#endif // TABLEWINDOW_H
