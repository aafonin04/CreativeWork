#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>

namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ReportWindow(QWidget *parent = nullptr);
    void setTableData(int, int,int,int, int,int);
    ~ReportWindow();

private:
    Ui::ReportWindow *ui;
};

#endif // REPORTWINDOW_H
