#include "ReportWindow.h"
#include "ui_reportwindow.h"
#include <QNetworkReply>

ReportWindow::ReportWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ReportWindow)
{
    ui->setupUi(this);
    ui->DatelineEdit->setReadOnly(true);
    setWindowTitle("Отчёт за день");
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    ui->DatelineEdit->setText(date);
    QFont font("Times New Roman", 14);
    ui->DatelineEdit->setFont(font);
    ui->DatelineEdit->setAlignment(Qt::AlignCenter);
}

void ReportWindow::setTableData(int dataClients, int dataBill,int dataClientsend, int dataBillend, int summ, int summ1)
{
    QTableWidgetItem* item = new QTableWidgetItem(QString::number(dataClients)); // создаем объект QTableWidgetItem и устанавливаем его значение
    ui->ReporttableWidget->setItem(0, 0, item); // устанавливаем объект в ячейку таблицы

    QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(dataBill));
    ui->ReporttableWidget->setItem(0, 1, item1);

    QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(dataClientsend));
    ui->ReporttableWidget->setItem(1, 0, item2);

    QTableWidgetItem* item3 = new QTableWidgetItem(QString::number(dataBillend));
    ui->ReporttableWidget->setItem(1, 1, item3);

    QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(dataClientsend-dataClients));
    ui->ReporttableWidget->setItem(2, 0, item4);

    QTableWidgetItem* item5 = new QTableWidgetItem(QString::number(dataBillend-dataBill));
    ui->ReporttableWidget->setItem(2, 1, item5);

    QTableWidgetItem* item6 = new QTableWidgetItem(QString::number(summ) + "(RUB)");
    ui->ReporttableWidget->setItem(0, 2, item6);

    QTableWidgetItem* item7 = new QTableWidgetItem(QString::number(summ1) + "(RUB)");
    ui->ReporttableWidget->setItem(1, 2, item7);

    QTableWidgetItem* item8 = new QTableWidgetItem(QString::number(summ1-summ) + "(RUB)");
    ui->ReporttableWidget->setItem(2, 2, item8);

    ui->ReporttableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->ReporttableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // запретить редактирование ячеек
    for (int i = 0; i < ui->ReporttableWidget->rowCount(); i++) {
        QTableWidgetItem* item = ui->ReporttableWidget->item(i, 0);
        item->setFlags(item->flags() & ~Qt::ItemIsEditable); // убрать флаг редактирования
    }
}

ReportWindow::~ReportWindow()
{
    delete ui;
}
