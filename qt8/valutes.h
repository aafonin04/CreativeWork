#ifndef VALUTES_H
#define VALUTES_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDomDocument>

class Valutes: public QMainWindow
{
    Q_OBJECT
public:
    explicit Valutes(QWidget *parent = nullptr);
private:
    QLineEdit* Dollars;
    QLineEdit* Uans;
    QLineEdit* Euros;
    void getResponse(QNetworkReply *reply);
    void sendData();
    bool findNode(const QDomNode &node,const QString &Name, const QString &number, QLineEdit *line);
};

#endif // VALUTES_H
