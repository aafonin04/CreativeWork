#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tablewindow.h"
#include "tablebills.h"
#include "regwindow.h"
#include "client.h"
#include "ReportWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
     QPushButton* getClientButton();
     QPushButton* getBillsButton();
     QPushButton* getResultButton();
    ~MainWindow();

private slots:
    void on_Client_btn_clicked();
    void on_Reg_btn_clicked();
    void on_Bills_btn_clicked();
    void on_Result_btn_clicked();
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    TableWindow* tableWindow;
    tablebills* billsWindow;
    regwindow* regWindow;
    ReportWindow* reportWindow;

};
#endif // MAINWINDOW_H

