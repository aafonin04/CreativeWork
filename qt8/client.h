#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <iostream>
#include <QMainWindow>
#include <QObject>
#include <QQuickItem>
#include <QSharedDataPointer>
#include <QWidget>
using namespace std;

class ClientData;

class Client: public QObject
{
    Q_OBJECT
public:
    QString get_rnd_FIO();
    QString get_rnd_passport();
    QString get_rnd_phone();
    QString get_rnd_code_word();
    QString get_rnd_money();
    QString get_rnd_num();
    void set_FIO(const QString& fio){FIO=fio;}
    void set_passport(const QString& pass){passport=pass;}
    void set_phone(const QString& p){phone=p;}
    void set_code_word(const QString& code){code_word=code;}
    void set_bills_numd(const QString& num){bills_num=num;}
    void set_money(const QString& dengi){money=dengi;}
    QString get_FIO()const{return FIO;}
    QString get_passport()const{return passport;}
    QString get_phone()const{return phone;}
    QString get_code_word()const{return code_word;}
    QString get_bills_num()const {return bills_num;}
    QString get_money()const {return money;}
    friend ostream& operator<<(ostream&, const Client&);
    friend istream& operator>>(istream&, Client&);

    Client();
    Client(const Client &);
    Client &operator=(const Client &);
    ~Client();

protected:
    QSharedDataPointer<ClientData> data;
    QString FIO;
    QString passport;
    QString phone;
    QString code_word;
    QString bills_num;
    QString money;
};

#endif // CLIENT_H
