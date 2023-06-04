#include "tablewindow.h"
#include <QHeaderView>
#include "client.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QAbstractItemModel>
#include "dwindow.h"
#include "addwindow.h"
#include "regwindow.h"
#include "codewindow.h"
#include <QStandardPaths>
#include <QList>

TableWindow::TableWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tableWidget = new QTableWidget(this);
    setCentralWidget(tableWidget);
    setWindowTitle("База данных клиентов");
    resize(1200, 600);
    QIcon windowIcon(":/bd.png");
    setWindowIcon(windowIcon);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tableWidget);
    Add_clnt_btn = new QPushButton("Добавить клиента", this);
    connect (Add_clnt_btn, &QPushButton::clicked, this, &TableWindow::on_add_btn_clicked);
    layout->addWidget(Add_clnt_btn);
    Del_clnt_btn=new QPushButton("Удалить клиента", this);
    connect(Del_clnt_btn, &QPushButton::clicked, this, &TableWindow::on_del_btn_clicked);
    layout->addWidget(Del_clnt_btn);
    Rand_clnt_btn = new QPushButton("Сгенерировать клиента", this);
    connect(Rand_clnt_btn, &QPushButton::clicked, this, &TableWindow::Rand_clnt_to_table);
    layout->addWidget(Rand_clnt_btn);
    Code_clnt_btn=new QPushButton("Получить кодовое слово");
    connect(Code_clnt_btn, &QPushButton::clicked, this, &TableWindow::on_code_btn_clicked);
    layout->addWidget(Code_clnt_btn);
    findclWindow=new findclient(this);
    Find_clnt_btn=new QPushButton("Поиск клиента", this);
    connect(Find_clnt_btn, &QPushButton::clicked, this, &TableWindow::on_find_btn_clicked);
    layout->addWidget(Find_clnt_btn);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    delclWindow=new dwindow(this);
    connect(delclWindow, &dwindow::deleteConfirmed, this, &TableWindow::confirmDeleteClient);
    addclWindow=new addwindow(this);
    connect(addclWindow, &addwindow::AddConfirmed, this, &TableWindow::ConfirmAddClient);
    findclWindow=new findclient(this);
    connect(findclWindow, &findclient::FindConfirmed, this, &TableWindow::confirmFindClient);
    codeclWindow=new codewindow(this);
    codeclWindow->setTableWindow(this);


}

QTableWidget* TableWindow::getTable(){
    return tableWidget;
}
void TableWindow::setTableData(const QList<QStringList>& data)
{
    int rowCount = data.size();
    int columnCount = data.isEmpty() ? 0 : data[0].size();

    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(columnCount);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер телефона" << "Паспорт"<<"Кодовое слово");
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < rowCount; ++i) {
        const QStringList& rowData = data[i];
        for (int j = 0; j < columnCount; ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(rowData.at(j)));
        }
    }
    tableWidget->setColumnHidden(3,true);
}

void TableWindow::Rand_clnt_to_table()
{
    Client client;
    QString fio = client.get_rnd_FIO();
    QString p = client.get_rnd_phone();
    QString pass = client.get_rnd_passport();
    QString code=client.get_rnd_code_word();
    int cnt_row=tableWidget->rowCount();
    tableWidget->insertRow(cnt_row);
    tableWidget->setItem(cnt_row, 0, new QTableWidgetItem(fio));
    tableWidget->setItem(cnt_row, 2, new QTableWidgetItem(pass));
    tableWidget->setItem(cnt_row, 1, new QTableWidgetItem(p));
    tableWidget->setItem(cnt_row, 3, new QTableWidgetItem(code));
    tableWidget->sortItems(0, Qt::AscendingOrder);
}

void TableWindow::on_code_btn_clicked(){
    codeclWindow->show();
}

void TableWindow::on_del_btn_clicked(){
     delclWindow->show();
}

void TableWindow::on_add_btn_clicked(){
     addclWindow->show();
}

void TableWindow::on_find_btn_clicked(){
    findclWindow->show();
}

void TableWindow::confirmDeleteClient(const QString& passport)
{
    bool f=false;
    int rowCount = tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        QTableWidgetItem* passportItem = tableWidget->item(i, 2);
        if (passportItem && passportItem->text() == passport) {
            tableWidget->removeRow(i);
            f=true;
            break;
        }
    }
    if (f==false){
        QMessageBox::critical(this,"Error","Клиент не найден");
        return;
    }
    QFile file("D:/qt8/Clients.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            int rowCount = tableWidget->rowCount();
            int columnCount = tableWidget->columnCount();
            for (int row = 0; row < rowCount; ++row)
            {
                for (int column = 0; column < columnCount; ++column)
                {
                    QTableWidgetItem* item = tableWidget->item(row, column);
                    if (item)
                    {
                        QString data = item->text();
                        stream << data << ",";
                    }
                    else
                    {
                        stream << ",";
                    }
                }
                stream << "\n";
            }
            file.close();
        }
        else
        {
            qDebug() << "Failed to open file for writing.";
        }
}

void TableWindow::ConfirmAddClient(const QString& FIO, const QString& Phone, const QString& Passport){
    if (FIO==""||Phone==""||Passport==""){
        QMessageBox::critical(this,"Ошибка","Заполните все поля.");
        return;
    }
    if (Phone.count()!=11||Passport.count()!=11){
        QMessageBox::critical(this,"Ошибка","Неправильный формат данных.");
        return;
    }
    QRegularExpression regex("\\d");
    if (FIO.contains(regex)) {
            QMessageBox::critical(this, "Ошибка", "Неправильный формат данных.");
            return;
    }
    Client client;
        int cnt_row=tableWidget->rowCount();
        tableWidget->insertRow(cnt_row);
        tableWidget->setItem(cnt_row, 0, new QTableWidgetItem(FIO));
        tableWidget->setItem(cnt_row, 1, new QTableWidgetItem(Phone));
        tableWidget->setItem(cnt_row, 2, new QTableWidgetItem(Passport));
        tableWidget->setItem(cnt_row, 3, new QTableWidgetItem(client.get_rnd_code_word()));
        tableWidget->sortItems(0, Qt::AscendingOrder);
        QFile file("D:/qt8/Clients.txt");
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream stream(&file);
                int rowCount = tableWidget->rowCount();
                int columnCount = tableWidget->columnCount();
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int column = 0; column < columnCount; ++column)
                    {
                        QTableWidgetItem* item = tableWidget->item(row, column);
                        if (item)
                        {
                            QString data = item->text();
                            stream << data << ",";
                        }
                        else
                        {
                            stream << ",";
                        }
                    }
                    stream << "\n";
                }
                file.close();
            }
            else
            {
                qDebug() << "Failed to open file for writing.";
            }
}

void TableWindow::confirmFindClient(const QString& FIO, const QString& Passport){
    QAbstractItemModel* model = tableWidget->model();
    int passcolumn=2;
    QModelIndexList passportIndexes = model->match(model->index(0, passcolumn), Qt::DisplayRole, Passport, -1, Qt::MatchExactly);
    int FIOcolumn=0;
    QModelIndexList FIOIndexes = model->match(model->index(0, FIOcolumn), Qt::DisplayRole, FIO, -1, Qt::MatchContains);
    QModelIndexList indexes = passportIndexes + FIOIndexes;
    if (FIO.isEmpty()||Passport.isEmpty()){
        QMessageBox::critical(this, "Ошибка", "Введите ФИО и номер паспорта.");
        return;
    }
    if (FIOIndexes.isEmpty()||passportIndexes.isEmpty()){
        QMessageBox::critical(this, "Ошибка", "Клиент не найден.");
        return;
    }
    if (!indexes.isEmpty()){
        QModelIndex index = indexes.first();
        tableWidget->scrollTo(index);
        for (int column = 0; column < model->columnCount(); ++column){
             tableWidget->item(index.row(), column)->setBackgroundColor(Qt::green);
        }
    }
}
