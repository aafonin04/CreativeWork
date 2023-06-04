#include "tablebills.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRegularExpression>
#include <QAbstractItemModel>
#include "client.h"
#include "tablewindow.h"
#include <QDebug>
#include <iostream>
#include "add_bill.h"
#include "givemoney.h"
#include "close_bill.h"

tablebills::tablebills(QWidget *parent)
    : QMainWindow(parent)
{
    tableBillsWidget = new QTableWidget(this);
    setCentralWidget(tableBillsWidget);
    setWindowTitle("Счета клиентов");
    resize(1200, 600);
    QIcon windowIcon(":/moneylogo.png");
    setWindowIcon(windowIcon);
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(tableBillsWidget);
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    add_bill_btn=new QPushButton("Открыть счёт",this);
    layout->addWidget(add_bill_btn);
    close_bill_btn=new QPushButton("Закрыть счёт", this);
    layout->addWidget(close_bill_btn);
    plus_bill_btn=new QPushButton("Пополнить счёт", this);
    layout->addWidget(plus_bill_btn);
    connect(plus_bill_btn,&QPushButton::clicked, this, &tablebills::on_plus_bill_btn_clicked);
    givemoney_btn=new QPushButton("Списать средства со счёта", this);
    layout->addWidget(givemoney_btn);
    offBills_btn=new QPushButton("Обнулить счёт",this);
    layout->addWidget(offBills_btn);
    valute_btn=new QPushButton("Курс валют", this);
    layout->addWidget(valute_btn);
    givemoney_window=new givemoney;
    connect(givemoney_window,&givemoney::givemoney_Confirmed,this,&tablebills::give_money_from_bills);
    connect(givemoney_btn, &QPushButton::clicked, this, &tablebills::on_givemoney_window_clicked);
    connect(add_bill_btn,&QPushButton::clicked,this,&tablebills::on_add_bill_btn_clicked);
    connect(offBills_btn,&QPushButton::clicked,this,&tablebills::on_off_bill_window_clicked);
    add_window_bills=new add_bill(this);
    connect(add_window_bills,&add_bill::bill_AddConfirmed,this,&tablebills::add_bills);
    cours=new Valutes;
    connect(valute_btn, &QPushButton::clicked,this,&tablebills::on_valute_btn_clicked);
    off_bill_window=new off_bill(this);
    connect(off_bill_window, &off_bill::bill_OffConfirmed, this, &tablebills::off_bill_methode);
    closebillWindow=new close_bill(this);
    connect(close_bill_btn, &QPushButton::clicked,this,&tablebills::close_bill_btn_clicked);
    connect(closebillWindow, &close_bill::closebill_confirmed, this, &tablebills::Close_Bill);
    plusemoney_window=new plusemoney(this);
    connect(plusemoney_window, &plusemoney::plusemoney_Confirmed, this, &tablebills::plus_money_on_bills);

}

void tablebills::setTableBillsData(const QList<QStringList> &billsdata){
    int rowCount = billsdata.size();
    int columnCount =billsdata.isEmpty() ? 0 : billsdata[0].size();

    tableBillsWidget->setRowCount(rowCount);
    tableBillsWidget->setColumnCount(columnCount);
    tableBillsWidget->setHorizontalHeaderLabels(QStringList() << "ФИО" << "Номер счёта" << "Баланс"<<"Паспорт");
    tableBillsWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < rowCount; ++i) {
        const QStringList& rowData = billsdata[i];
        for (int j = 0; j < columnCount; ++j) {
            tableBillsWidget->setItem(i, j, new QTableWidgetItem(rowData.at(j)));
        }
    }
    int balanceColumn = 2;
    int rowCount1 = tableBillsWidget->rowCount();
    for (int row = 0; row < rowCount1; ++row)
    {
        QTableWidgetItem* item = tableBillsWidget->item(row, balanceColumn);
        if (item)
        {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void tablebills::on_givemoney_window_clicked()
{
    givemoney_window->show();
}

void tablebills::on_valute_btn_clicked()
{
cours->show();
}

void tablebills::on_add_bill_btn_clicked()
{
    add_window_bills->show();
}

void tablebills::on_off_bill_window_clicked()
{
    off_bill_window->show();
}

void tablebills::close_bill_btn_clicked()
{
    closebillWindow->show();
}

void tablebills::on_plus_bill_btn_clicked()
{
    plusemoney_window->show();
}


void tablebills::give_money_from_bills(const QString& Num, const QString& Summ, const QString& Valute,const QString& CodeWord)
{
    int rowCount = tableBillsWidget->rowCount();

    // Проходим по каждой строке таблицы
    for (int row = 0; row < rowCount; ++row)
    {
        // Получаем номер счета из текущей строки
        QTableWidgetItem* numItem = tableBillsWidget->item(row, 1);
        if (numItem && numItem->text() == Num)
        {
            // Найден счет с указанным номером
            // Получаем текущий баланс счета
            QTableWidgetItem* balanceItem = tableBillsWidget->item(row, 2);
            if (balanceItem)
            {
                // Получаем текущий баланс
                QString currentBalance = balanceItem->text();

                // Извлекаем числовое значение суммы из строки баланса
                QString balanceValueString = currentBalance.split('(').at(0);
                double currentBalanceValue = balanceValueString.toDouble();

                // Получаем валюту счета
                QString accountCurrency = currentBalance.mid(currentBalance.indexOf('(') + 1, currentBalance.indexOf(')') - currentBalance.indexOf('(') - 1);

                // Проверяем, достаточно ли средств на счете
                double requestedAmount = Summ.toDouble();
                if ((currentBalanceValue >= requestedAmount))
                {
                    // Проверяем, совпадают ли валюты счета и списания
                    if ((accountCurrency == Valute)&&(((requestedAmount>=50000)&&( Valute=="RUB"))||((requestedAmount>=1000)&&( Valute=="USD"))||((requestedAmount>=5000)&&( Valute=="CNY"))))
                    {
                        //QMessageBox::information(this, "Кодовое слово", "Введите кодовое слово");
                        QFile file("D:/qt8/Clients.txt");
                        QFile file1("D:/qt8/ClientsBills.txt");
                        if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
                        QTextStream stream(&file);
                        QTextStream stream1(&file1);
                        int i=0;
                        while (!stream.atEnd())
                        {
                            QString line = stream.readLine();
                            QStringList data = line.split(",");
                            QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                            QString SavedCodeWord=data.value(3);
                            QString SavedPassport=data.value(2);
                            QString line1 = stream1.readLine();
                            QStringList data1 = line1.split(",");
                            QString SavedPassport1=data1.value(3);
                            if ((Num== BilNumItem->text())&&(CodeWord==SavedCodeWord)&&(SavedPassport==SavedPassport1))
                            {
                                // Списываем средства без комиссии
                                double newBalanceValue = currentBalanceValue - requestedAmount;
                                QString stringsum = QString::number(requestedAmount);
                                // Обновляем значение баланса в таблице
                                balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + Valute + ")");
                                // Выводим сообщение об успешном списании
                                QMessageBox::information(this, "Операция выполнена", stringsum + Valute + " успешно списаны со счета " + Num);
                                return;
                            }

                            i++;
                        }
                        file.close();
                        file1.close();
                        QMessageBox::warning(this, "Препдупреждение", "Для списания средств введите кодовое слово");
                    }
                    }
                    if ((accountCurrency == Valute)&&(((requestedAmount<50000)&&( Valute=="RUB"))||((requestedAmount<1000)&&( Valute=="USD"))||((requestedAmount<5000)&&( Valute=="CNY")))){
                        // Списываем средства без комиссии
                        double newBalanceValue = currentBalanceValue - requestedAmount;
                        QString stringsum = QString::number(requestedAmount);
                        // Обновляем значение баланса в таблице
                        balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + Valute + ")");
                        // Выводим сообщение об успешном списании
                        QMessageBox::information(this, "Операция выполнена", stringsum + Valute + " успешно списаны со счета " + Num);
                    }
                    else
                    {
                        if ((accountCurrency != Valute)&&(((requestedAmount>=50000)&&( Valute=="RUB"))||((requestedAmount>=1000)&&( Valute=="USD"))||((requestedAmount>=5000)&&( Valute=="CNY")))){
                            QFile file("D:/qt8/Clients.txt");
                            QFile file1("D:/qt8/ClientsBills.txt");
                            if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
                                QTextStream stream(&file);
                                QTextStream stream1(&file1);
                                QString SavedCodeWord;  // Переменная для хранения сохраненного кодового слова
                                int i = 0;
                                bool found = false;  // Флаг, указывающий, был ли найден счет совпадающий с введенным номером счета

                                // Находим сохраненное кодовое слово и проверяем, соответствует ли оно введенному кодовому слову
                                while (!stream.atEnd() && !found){
                                    QString line = stream.readLine();
                                    QStringList data = line.split(",");
                                    QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                                    QString line1 = stream1.readLine();
                                    QStringList data1 = line1.split(",");
                                    if (Num == BilNumItem->text()){
                                        SavedCodeWord = data.value(3);
                                        found = true;
                                    }
                                    i++;
                                }
                                file.close();
                                file1.close();

                                if (!found){
                                    QMessageBox::warning(this, "Предупреждение", "Счет не найден.");
                                    return;
                                }

                                if (CodeWord != SavedCodeWord){
                                    QMessageBox::warning(this, "Предупреждение", "Для списания средств введите кодовое слово.");
                                    return;
                                }

                                // Продолжаем выполнение кода только если кодовое слово совпадает

                                // Счет и списание в разных валютах, применяем курс и комиссию
                                double convertedAmount = 0.0;
                                double commission = 0.0;

                                if (accountCurrency == "RUB" && Valute == "USD"){
                                    convertedAmount = requestedAmount * 79.9;
                                    commission = convertedAmount * 0.1;
                                }
                                else if (accountCurrency == "USD" && Valute == "RUB"){
                                    convertedAmount = requestedAmount / 79.9;
                                    commission = convertedAmount * 0.1;
                                }
                                else if (accountCurrency == "RUB" && Valute == "CNY"){
                                    convertedAmount = requestedAmount * 11.3;
                                    commission = convertedAmount * 0.1;
                                }
                                else if (accountCurrency == "CNY" && Valute == "RUB"){
                                    convertedAmount = requestedAmount / 11.3;
                                    commission = convertedAmount * 0.1;
                                }
                                else if (accountCurrency == "CNY" && Valute == "USD"){
                                    convertedAmount = requestedAmount * 7.06;
                                    commission = convertedAmount * 0.1;
                                }
                                else if (accountCurrency == "USD" && Valute == "CNY"){
                                    convertedAmount = requestedAmount / 7.06;
                                    commission = convertedAmount * 0.1;
                                }

                                // Вычитаем сконвертированную сумму списания и комиссию из текущего баланса
                                double newBalanceValue = currentBalanceValue - (convertedAmount + commission);
                                QString stringsum1 = QString::number(convertedAmount + commission);
                                // Обновляем значение баланса в таблице
                                balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + accountCurrency + ")");
                                // Выводим сообщение об успешном списании
                                QMessageBox::information(this, "Операция выполнена", stringsum1 + Valute + " с учетом комиссии успешно списаны со счета " + Num);
                            }
                            else{
                                qDebug() << "Failed to open file for reading.";
                            }
                        }
                }
                if ((accountCurrency != Valute)&&(((requestedAmount<50000)&&( Valute=="RUB"))||((requestedAmount<1000)&&( Valute=="USD"))||((requestedAmount<5000)&&( Valute=="CNY")))){
                    QFile file("D:/qt8/Clients.txt");
                    QFile file1("D:/qt8/ClientsBills.txt");
                    if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
                    QTextStream stream(&file);
                    QTextStream stream1(&file1);
                    int i=0;
                    while (!stream.atEnd()){
                    QString line = stream.readLine();
                    QStringList data = line.split(",");
                    QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                    QString line1 = stream1.readLine();
                    QStringList data1 = line1.split(",");
                    if (Num== BilNumItem->text()){
                    // Счет и списание в разных валютах, применяем курс и комиссию
                    double convertedAmount = 0.0;
                    double commission = 0.0;

                    if (accountCurrency == "RUB" && Valute == "USD")
                    {
                        convertedAmount = requestedAmount * 79.9;
                        commission = convertedAmount * 0.1;
                    }
                    else if (accountCurrency == "USD" && Valute == "RUB")
                    {
                        convertedAmount = requestedAmount / 79.9;
                        commission = convertedAmount * 0.1;
                    }
                    else if (accountCurrency == "RUB" && Valute == "CNY")
                    {
                        convertedAmount = requestedAmount * 11.3;
                        commission = convertedAmount * 0.1;
                    }
                    else if (accountCurrency == "CNY" && Valute == "RUB")
                    {
                        convertedAmount = requestedAmount / 11.3;
                        commission = convertedAmount * 0.1;
                    }
                    else if (accountCurrency == "CNY" && Valute == "USD")
                    {
                        convertedAmount = requestedAmount * 7.06;
                        commission = convertedAmount * 0.1;
                    }
                    else if (accountCurrency == "USD" && Valute == "CNY")
                    {
                        convertedAmount = requestedAmount / 7.06;
                        commission = convertedAmount * 0.1;
                    }

                    // Вычитаем сконвертированную сумму списания и комиссию из текущего баланса
                    double newBalanceValue = currentBalanceValue - (convertedAmount + commission);
                    QString stringsum2 = QString::number(convertedAmount + commission);
                    // Обновляем значение баланса в таблице
                    balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + accountCurrency + ")");

                    // Выводим сообщение об успешном списании
                    QMessageBox::information(this, "Операция выполнена", stringsum2 + accountCurrency + " с учетом комиссии успешно списаны со счета " + Num);
                    }
                    i++;
                    }
                    file.close();
                    file1.close();
                }

          }
                }
                else
                {
                    // Средств на счете недостаточно
                    QMessageBox::warning(this, "Ошибка", "Недостаточно средств на счете " + Num);
                }
            }

            else
            {
                // Ошибка: баланс не найден в таблице
                QMessageBox::warning(this, "Ошибка", "Не удалось найти баланс для счета " + Num);
            }

            // Прерываем цикл, так как счет уже найден и списание выполнено
            break;
        }
    }

    QFile file("D:/qt8/ClientsBills.txt");
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            int rowCount = tableBillsWidget->rowCount();
            int columnCount = tableBillsWidget->columnCount();
            for (int row = 0; row < rowCount; ++row)
            {
                for (int column = 0; column < columnCount; ++column)
                {
                    QTableWidgetItem* item = tableBillsWidget->item(row, column);
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

void tablebills::plus_money_on_bills(const QString& Num, const QString& Summ, const QString& Valute)
{
    int rowCount = tableBillsWidget->rowCount();

        // Проходим по каждой строке таблицы
        for (int row = 0; row < rowCount; ++row)
        {
            // Получаем номер счета из текущей строки
            QTableWidgetItem* numItem = tableBillsWidget->item(row, 1);
            if (numItem && numItem->text() == Num)
            {
                // Найден счет с указанным номером
                // Получаем текущий баланс счета
                QTableWidgetItem* balanceItem = tableBillsWidget->item(row, 2);
                if (balanceItem)
                {
                    // Получаем текущий баланс
                    QString currentBalance = balanceItem->text();

                    // Извлекаем числовое значение суммы из строки баланса
                    QString balanceValueString = currentBalance.split('(').at(0);
                    double currentBalanceValue = balanceValueString.toDouble();

                    // Получаем валюту счета
                    QString accountCurrency = currentBalance.mid(currentBalance.indexOf('(') + 1, currentBalance.indexOf(')') - currentBalance.indexOf('(') - 1);

                    double requestedAmount = Summ.toDouble();
                        // Проверяем, совпадают ли валюты счета и списания
                    if (currentBalance=="0"){
                        QFile file("D:/qt8/Clients.txt");
                        QFile file1("D:/qt8/ClientsBills.txt");
                        if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
                        QTextStream stream(&file);
                        QTextStream stream1(&file1);
                        int i=0;
                        while (!stream.atEnd())
                        {
                            QString line = stream.readLine();
                            QStringList data = line.split(",");
                            QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                            QString line1 = stream1.readLine();
                            QStringList data1 = line1.split(",");
                            if (Num== BilNumItem->text())
                            {
                                // Списываем средства без комиссии
                                double newBalanceValue = requestedAmount;
                                QString stringsum = QString::number(requestedAmount);
                                // Обновляем значение баланса в таблице
                                balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + Valute + ")");
                                // Выводим сообщение об успешном списании
                                QMessageBox::information(this, "Операция выполнена", stringsum + Valute + " успешно добавлены на счёт " + Num);
                                return;
                            }

                            i++;
                        }
                        file.close();
                        file1.close();

                    }
                    }
                        if (accountCurrency == Valute)
                        {

                            QFile file("D:/qt8/Clients.txt");
                            QFile file1("D:/qt8/ClientsBills.txt");
                            if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
                            QTextStream stream(&file);
                            QTextStream stream1(&file1);
                            int i=0;
                            while (!stream.atEnd())
                            {
                                QString line = stream.readLine();
                                QStringList data = line.split(",");
                                QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                                QString line1 = stream1.readLine();
                                QStringList data1 = line1.split(",");
                                if (Num== BilNumItem->text())
                                {
                                    // Списываем средства без комиссии
                                    double newBalanceValue = currentBalanceValue + requestedAmount;
                                    QString stringsum = QString::number(requestedAmount);
                                    // Обновляем значение баланса в таблице
                                    balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + Valute + ")");
                                    // Выводим сообщение об успешном списании
                                    QMessageBox::information(this, "Операция выполнена", stringsum + Valute + " успешно добавлены на счёт " + Num);
                                }

                                i++;
                            }
                            file.close();
                            file1.close();

                        }
                        }

                    if (accountCurrency != Valute){
                        // Счет и списание в разных валютах, применяем курс и комиссию
                        double convertedAmount = 0.0;
                        double commission = 0.0;

                        if (accountCurrency == "RUB" && Valute == "USD")
                        {
                            convertedAmount = requestedAmount * 79.9;
                            commission = convertedAmount * 0.1;
                        }
                        else if (accountCurrency == "USD" && Valute == "RUB")
                        {
                            convertedAmount = requestedAmount / 79.9;
                            commission = convertedAmount * 0.1;
                        }
                        else if (accountCurrency == "RUB" && Valute == "CNY")
                        {
                            convertedAmount = requestedAmount * 11.3;
                            commission = convertedAmount * 0.1;
                        }
                        else if (accountCurrency == "CNY" && Valute == "RUB")
                        {
                            convertedAmount = requestedAmount / 11.3;
                            commission = convertedAmount * 0.1;
                        }
                        else if (accountCurrency == "CNY" && Valute == "USD")
                        {
                            convertedAmount = requestedAmount * 7.06;
                            commission = convertedAmount * 0.1;
                        }
                        else if (accountCurrency == "USD" && Valute == "CNY")
                        {
                            convertedAmount = requestedAmount / 7.06;
                            commission = convertedAmount * 0.1;
                        }

                        // Вычитаем сконвертированную сумму списания и комиссию из текущего баланса
                        double newBalanceValue = currentBalanceValue + (convertedAmount - commission);
                        QString stringsum2 = QString::number(convertedAmount - commission);
                        // Обновляем значение баланса в таблице
                        balanceItem->setText(QString::number(newBalanceValue, 'f', 2) + "(" + accountCurrency + ")");

                        // Выводим сообщение об успешном списании
                        QMessageBox::information(this, "Операция выполнена", stringsum2 + accountCurrency + " с учетом комиссии успешно добавлены на счёт " + Num);
                    }

              }

                else
                {
                    // Ошибка: баланс не найден в таблице
                    QMessageBox::warning(this, "Ошибка", "Не удалось найти баланс для счета " + Num);
                }

                // Прерываем цикл, так как счет уже найден и списание выполнено
                break;
            }
        }

       QFile file2("D:/qt8/ClientsBills.txt");
            if (file2.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream stream(&file2);
                int rowCount = tableBillsWidget->rowCount();
                int columnCount = tableBillsWidget->columnCount();
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int column = 0; column < columnCount; ++column)
                    {
                        QTableWidgetItem* item = tableBillsWidget->item(row, column);
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
                file2.close();
            }
            else
            {
                qDebug() << "Failed to open file for writing.";
            }
}

void tablebills::add_bills(const QString& FIO, const QString& passport)
{
    QFile file("D:/qt8/Clients.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            bool found = false;
            while (!stream.atEnd())
            {
                QString line = stream.readLine();
                QStringList data = line.split(",");
                QString SavedFIO=data.value(0);
                QString SavedPassport=data.value(2);
                if ((SavedFIO==FIO)&&(SavedPassport==passport))
                {
                    found = true;
                    break;
                }
            }
            file.close();
            if (found){
            Client a;
            int cnt_row = tableBillsWidget->rowCount();
            tableBillsWidget->insertRow(cnt_row);
            tableBillsWidget->setItem(cnt_row, 0, new QTableWidgetItem(FIO));
            tableBillsWidget->setItem(cnt_row, 1, new QTableWidgetItem(a.get_rnd_num()));
            tableBillsWidget->setItem(cnt_row, 2, new QTableWidgetItem("0"));
            tableBillsWidget->setItem(cnt_row, 3, new QTableWidgetItem(passport));
            tableBillsWidget->sortItems(0, Qt::AscendingOrder);
            }
            else{
                 QMessageBox::critical(this,"Ошибка","Клиент не найден.");
            }
        }
        QFile file1("D:/qt8/ClientsBills.txt");
            if (file1.open(QIODevice::WriteOnly | QIODevice::Text))
            {

                QTextStream stream(&file1);
                int rowCount = tableBillsWidget->rowCount();
                int columnCount = tableBillsWidget->columnCount();
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int column = 0; column < columnCount; ++column)
                    {
                        QTableWidgetItem* item = tableBillsWidget->item(row, column);
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
                file1.close();
            }
            else
            {
                qDebug() << "Failed to open file for writing.";
            }
}

void tablebills::off_bill_methode(const QString& Bill_Num, const QString& CodeWord)
{
    bool f = false;
    QFile file("D:/qt8/Clients.txt");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            int i=0;
            while (!stream.atEnd())
            {
                QString line = stream.readLine();
                QStringList data = line.split(",");
                QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
                QString SavedCodeWord=data.value(3);
                if ((Bill_Num== BilNumItem->text())&&(CodeWord==SavedCodeWord))
                {
                    tableBillsWidget->setItem(i, 2, new QTableWidgetItem("0"));
                    f=true;
                    break;
                }
                i++;
            }
            file.close();
            if (f==false){
                 QMessageBox::critical(this,"Ошибка","Клиент не найден.");
            }
        }
        QFile file1("D:/qt8/ClientsBills.txt");
            if (file1.open(QIODevice::WriteOnly | QIODevice::Text))
            {

                QTextStream stream(&file1);
                int rowCount = tableBillsWidget->rowCount();
                int columnCount = tableBillsWidget->columnCount();
                for (int row = 0; row < rowCount; ++row)
                {
                    for (int column = 0; column < columnCount; ++column)
                    {
                        QTableWidgetItem* item = tableBillsWidget->item(row, column);
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
                file1.close();
            }
            else
            {
                qDebug() << "Failed to open file for writing.";
            }
}

void tablebills::Close_Bill(const QString& Num)
{
    QFile file("D:/qt8/Clients.txt");
    QFile file1("D:/qt8/ClientsBills.txt");
    bool f=false;
    if ((file.open(QIODevice::ReadOnly | QIODevice::Text))&&(file1.open(QIODevice::ReadOnly | QIODevice::Text))){
    QTextStream stream(&file);
    QTextStream stream1(&file1);
    int i=0;
    while (!stream.atEnd()&&!stream1.atEnd())
    {
        QString line = stream.readLine();
        QStringList data = line.split(",");
        QString line1 = stream1.readLine();
        QStringList data1 = line1.split(",");
        QTableWidgetItem* BilNumItem = tableBillsWidget->item(i, 1);
        QTableWidgetItem* Blance = tableBillsWidget->item(i, 2);
        if (Num== BilNumItem->text())
        {
            f=true;
            if (Blance->text()=="0"){
                    tableBillsWidget->removeRow(i);
                    QFile file2("D:/qt8/ClientsBills.txt");
                        if (file2.open(QIODevice::WriteOnly | QIODevice::Text))
                        {
                            QTextStream stream2(&file2);
                            int rowCount = tableBillsWidget->rowCount();
                            int columnCount = tableBillsWidget->columnCount();
                            for (int row = 0; row < rowCount; ++row)
                            {
                                for (int column = 0; column < columnCount; ++column)
                                {
                                    QTableWidgetItem* item = tableBillsWidget->item(row, column);
                                    if (item)
                                    {
                                        QString data = item->text();
                                        stream2 << data << ",";
                                    }
                                    else
                                    {
                                        stream2 << ",";
                                    }
                                }
                                stream2 << "\n";
                            }
                            file2.close();
                        }
                        else
                        {
                            qDebug() << "Failed to open file for writing.";
                        }
                        break;
            }
            else{
                QMessageBox::critical(this,"Ошибка","Необходимо обнулить счёт");
                return;
            }
        }

        i++;
    }
    }
    if (f==false){
        QMessageBox::critical(this, "Ошибка", "Счёт не найден");
    }
    file.close();
    file1.close();

}
