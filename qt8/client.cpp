#include "client.h"
#include <QTime>
#include <QTimer>
#include <QRandomGenerator>
#include <ctime>
using namespace std;

class ClientData : public QSharedData
{
public:

};

Client::Client() : data(new ClientData)
{
    srand(QDateTime::currentMSecsSinceEpoch());

}

Client::Client(const Client &rhs) : data(rhs.data)
{

}

Client &Client::operator=(const Client &rhs)
{
    if (this != &rhs)
        data.operator=(rhs.data);
    return *this;
}
Client::~Client()
{

}



QString Client::get_rnd_FIO(){
    QRandomGenerator* rd=QRandomGenerator::global();
            for (int i=0;i<10;i++){
                rd->bounded(0,9);
        }
    QString name[10] = { "Александр", "Борис", "Виктор", "Григорий", "Дмитрий", "Евгений", "Иван", "Николай", "Михаил", "Олег" };
    QString patronymic[10] = { "Александрович", "Борисович", "Викторович", "Григорьевич", "Дмитриевич", "Евгеньевич", "Иванович", "Николаевич", "Михайлович", "Олегович" };
    QString surname[10] = { "Александров", "Борисов", "Викторов", "Григорьев", "Дмитриев", "Евгеньев", "Иванов", "Николаев", "Михайлов", "Олегов" };
    QString fio = surname[rd->bounded(0,9)]+ " "+ name[rd->bounded(0,9)] +" "+patronymic[rd->bounded(0,9)];
    FIO=fio;
    return fio;
}

QString Client::get_rnd_phone(){
    QRandomGenerator* rd=QRandomGenerator::global();
        for (int i=0;i<10;i++){
            rd->bounded(0,9);
    }
    QString num[10] = { "0","1","2","3","4","5","6","7","8","9"};
    QString p = "89"+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)];
    phone=p;
    return p;
}
QString Client::get_rnd_money(){
    QRandomGenerator* rd=QRandomGenerator::global();
    QRandomGenerator* rd2=QRandomGenerator::global();
    for(int i=0;i<3;i++){
    rd->bounded(0,3);}
    for(int i=0;i<10;i++){
        rd2->bounded(0,9);
    }
    QString value[3]={"₽","$","¥"};
    QString num[10]={ "0","1","2","3","4","5","6","7","8","9"};
    QString mc="";
    for (int i=0; i<=rd2->bounded(2,10);++i){
       mc=mc+num[rd2->bounded(0,9)];
       if (mc[0]=="0"){
           mc="0";
           break;
       }
   }
    mc=value[rd->bounded(0,3)]+mc;
    money=mc;
    return mc;
}

QString Client::get_rnd_passport(){
    QRandomGenerator* rd=QRandomGenerator::global();
        for (int i=0;i<10;i++){
            rd->bounded(0,9);
    }
    QString num[10] = { "0","1","2","3","4","5","6","7","8","9"};
    QString num1[9] = { "1","2","3","4","5","6","7","8","9"};
    QString pass = num1[rd->bounded(0,9)] + num[rd->bounded(0,9)] + num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+" "+num1[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)]+num[rd->bounded(0,9)];
    passport=pass;
    return pass;
}
QString Client::get_rnd_code_word(){
    QRandomGenerator*rd=QRandomGenerator::global();
    for(int i=0;i<20;i++){
        rd->bounded(0,19);
    }
    QString word[20]={"Дева","Водолей","Козерог","Весы","Раки","Кошечка","Информатика","Красный","Black","Близнецы","Футбол","Циркуль","Петя","Виктор","QEwRot","Stone","Tyunsh","H7jK9d","E3mR8s","F5nT2c"};
    QString password=word[rd->bounded(0,19)];
    code_word=password;
    return password;
}

QString Client::get_rnd_num()
{
    QRandomGenerator* rd=QRandomGenerator::global();
        for (int i=0;i<10;i++){
            rd->bounded(0,9);
        }
    QString bill[10] = { "05","14","27","32","48","57","69","74","83","91"};
    QString mon = "4018"+bill[rd->bounded(0,9)] + bill[rd->bounded(0,9)] + bill[rd->bounded(0,9)]+bill[rd->bounded(0,9)]+bill[rd->bounded(0,9)]+bill[rd->bounded(0,9)]+bill[rd->bounded(0,9)]+bill[rd->bounded(0,9)];
    bills_num=mon;
    return mon;
}

