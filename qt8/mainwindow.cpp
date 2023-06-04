#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "tablewindow.h"
#include "regwindow.h"
#include "ReportWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAction>
#include <QRegion>
#include "tablebills.h"
#include "ReportWindow.h"
#include <QRandomGenerator>
#include <QVector>


QVector <Client*> clientvector1;
QVector <Client*> billvector1;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
ui->setupUi(this);
  ui->Client_btn->setEnabled(false);
  ui->Bills_btn->setEnabled(false);
  ui->Result_btn->setEnabled(false);
  tableWindow = new TableWindow(this);
  //tableWindow->setWindowModality(Qt::ApplicationModal);
  regWindow = new regwindow(this);
  setWindowTitle("АРМ работника банка");
  QIcon windowIcon(":/main2.png");
  setWindowIcon(windowIcon);
  QPixmap backgroundImage(":/fon.jpg");
  QPalette palette;
  palette.setBrush(QPalette::Background, backgroundImage);
  this->setPalette(palette);
  regWindow->setMainWindow(this);
  billsWindow=new tablebills(this);
  reportWindow=new ReportWindow(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
QPushButton* MainWindow::getClientButton()
{
    return ui->Client_btn;
}
QPushButton* MainWindow::getBillsButton(){
    return ui->Bills_btn;
}

QPushButton* MainWindow::getResultButton(){
    return ui->Result_btn;
}

void set_clientvector(QVector <Client*>& clientvector)
{
    QFile file("D:/qt8/Clients.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file: " << file.errorString();
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(",");
            if (data.size() == 5) {
                Client* client = new Client;
                client->set_FIO(data[0]);
                client->set_phone(data[1]);
                client->set_passport(data[2]);
                client->set_code_word(data[3]);
                clientvector.push_back(client);
            }
        }

        file.close();
}

void set_billvector(QVector <Client*>& billvector)
{
    QFile file("D:/qt8/ClientsBills.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file: " << file.errorString();
            return;
        }

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList data = line.split(",");
            if (data.size() == 5) {
                Client* client1 = new Client;
                client1->set_FIO(data[0]);
                client1->set_passport(data[3]);
                client1->set_bills_numd(data[1]);
                client1->set_money(data[2]);
                billvector.push_back(client1);
            }
        }

        file.close();
}
void MainWindow::on_Client_btn_clicked()
{
        set_clientvector(clientvector1);
        QList<QStringList> tableData;
        for (int i = 0; i <clientvector1.size(); ++i) {
            QStringList rowData;
            rowData << clientvector1[i]->get_FIO() << clientvector1[i]->get_phone() << clientvector1[i]->get_passport() << clientvector1[i]->get_code_word();
            tableData.append(rowData);
        }
        tableWindow->setTableData(tableData);
        tableWindow->show();
        clientvector1.clear();

}


void MainWindow::on_Reg_btn_clicked()
{
    regWindow->show();
}


void MainWindow::on_Bills_btn_clicked()
{
       set_billvector(billvector1);
       QList<QStringList> tablebillsData;
       for (int i = 0; i < billvector1.size(); ++i) {
           QStringList rowData;
           rowData << billvector1[i]->get_FIO() << billvector1[i]->get_bills_num() << billvector1[i]->get_money()<<billvector1[i]->get_passport();
           tablebillsData.append(rowData);
       }
    billsWindow->setTableBillsData(tablebillsData);
    billsWindow->show();
    billvector1.clear();
}

void MainWindow::on_Result_btn_clicked()
{
    int count = 0;
    int count1=0;
    int count2=0;
    int count3=0;
    QFile file("D:/qt8/StartClients.txt"); // создаем объект файла
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in(&file); // создаем текстовый поток для чтения из файла // счетчик строк
        while (!in.atEnd()) // пока не достигнут конец файла
        {
            QString line = in.readLine(); // читаем строку из файла
            count++; // увеличиваем счетчик строк
        }
        file.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file.errorString(); // выводим сообщение об ошибке
    }

    QFile file1("D:/qt8/StartClientsBills.txt"); // создаем объект файла
    if (file1.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in1(&file1); // создаем текстовый поток для чтения из файла
        while (!in1.atEnd()) // пока не достигнут конец файла
        {
            QString line = in1.readLine(); // читаем строку из файла
            count1++; // увеличиваем счетчик строк
        }
        file1.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file1.errorString(); // выводим сообщение об ошибке
    }

    QFile file2("D:/qt8/Clients.txt"); // создаем объект файла
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in2(&file2); // создаем текстовый поток для чтения из файла // счетчик строк
        while (!in2.atEnd()) // пока не достигнут конец файла
        {
            QString line = in2.readLine(); // читаем строку из файла
            count2++; // увеличиваем счетчик строк
        }
        file2.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file2.errorString(); // выводим сообщение об ошибке
    }

    QFile file3("D:/qt8/ClientsBills.txt"); // создаем объект файла
    if (file3.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in3(&file3); // создаем текстовый поток для чтения из файла // счетчик строк
        while (!in3.atEnd()) // пока не достигнут конец файла
        {
            QString line = in3.readLine(); // читаем строку из файла
            count3++; // увеличиваем счетчик строк
        }
        file3.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file3.errorString(); // выводим сообщение об ошибке
    }

    QFile file4("D:/qt8/StartClientsBills.txt"); // создаем объект файла
    float summ=0;
    if (file4.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in4(&file4); // создаем текстовый поток для чтения из файла
        while (!in4.atEnd()) // пока не достигнут конец файла
        {
            QString row = in4.readLine();
            QStringList data = row.split(",");
            if (data[2]!="0"){
            QString moneyString = data[2].split("(")[0];
            QString currency = data[2].split("(")[1].replace(")", "");
            float money = moneyString.toFloat();
            if (currency=="RUB"){
                summ=summ+money;
            }
            if (currency=="USD"){
                summ=summ+money*79.9;
            }
            if (currency=="CNY"){
                summ=summ+money*11.3;
            }
            }
        }
        file4.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file4.errorString(); // выводим сообщение об ошибке
    }

    QFile file5("D:/qt8/ClientsBills.txt"); // создаем объект файла
    float summ1=0;
    if (file5.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем файл для чтения
    {
        QTextStream in5(&file5); // создаем текстовый поток для чтения из файла
        while (!in5.atEnd()) // пока не достигнут конец файла
        {
            QString row = in5.readLine();
            QStringList data = row.split(",");
            if (data[2]!="0"){
            QString moneyString = data[2].split("(")[0];
            QString currency = data[2].split("(")[1].replace(")", "");
            float money = moneyString.toFloat();
            if (currency=="RUB"){
                summ1=summ1+money;
            }
            if (currency=="USD"){
                summ1=summ1+money*79.9;
            }
            if (currency=="CNY"){
                summ1=summ1+money*11.3;
            }
            }
        }
        file5.close(); // закрываем файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << file5.errorString(); // выводим сообщение об ошибке
    }

    reportWindow->setTableData(count,count1,count2,count3,summ,summ1);
    reportWindow->show();

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QString inputFilename = "D:/qt8/Clients.txt"; // имя входного файла
    QString outputFilename = "D:/qt8/StartClients.txt"; // имя выходного файла
    QFile inputFile(inputFilename); // создаем объект входного файла
    QFile outputFile(outputFilename); // создаем объект выходного файла
    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем входной файл для чтения
    {
        if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) // открываем выходной файл для записи
        {
            QTextStream in(&inputFile); // создаем текстовый поток для чтения из входного файла
            QTextStream out(&outputFile); // создаем текстовый поток для записи в выходной файл
            while (!in.atEnd()) // пока не достигнут конец входного файла
            {
                QString line = in.readLine(); // читаем строку из входного файла
                out << line << endl; // записываем строку в выходной файл с символом перевода строки
            }
            outputFile.close(); // закрываем выходной файл
        }
        else
        {
            qDebug() << "Ошибка открытия файла:" << outputFile.errorString(); // выводим сообщение об ошибке
        }
        inputFile.close(); // закрываем входной файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << inputFile.errorString(); // выводим сообщение об ошибке
    }

    QString inputFilename1 = "D:/qt8/ClientsBills.txt"; // имя входного файла
    QString outputFilename1 = "D:/qt8/StartClientsBills.txt"; // имя выходного файла
    QFile inputFile1(inputFilename1); // создаем объект входного файла
    QFile outputFile1(outputFilename1); // создаем объект выходного файла
    if (inputFile1.open(QIODevice::ReadOnly | QIODevice::Text)) // открываем входной файл для чтения
    {
        if (outputFile1.open(QIODevice::WriteOnly | QIODevice::Text)) // открываем выходной файл для записи
        {
            QTextStream in(&inputFile1); // создаем текстовый поток для чтения из входного файла
            QTextStream out(&outputFile1); // создаем текстовый поток для записи в выходной файл
            while (!in.atEnd()) // пока не достигнут конец входного файла
            {
                QString line = in.readLine(); // читаем строку из входного файла
                out << line << endl; // записываем строку в выходной файл с символом перевода строки
            }
            outputFile1.close(); // закрываем выходной файл
        }
        else
        {
            qDebug() << "Ошибка открытия файла:" << outputFile1.errorString(); // выводим сообщение об ошибке
        }
        inputFile1.close(); // закрываем входной файл
    }
    else
    {
        qDebug() << "Ошибка открытия файла:" << inputFile1.errorString(); // выводим сообщение об ошибке
    }



    // передаем управление стандартной обработке события
    QMainWindow::closeEvent(event);
}


