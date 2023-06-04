#include "valutes.h"
#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDomDocument>
#include<QFormLayout>


Valutes::Valutes(QWidget *parent) :
    QMainWindow(parent)
{
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Курс валют");
    resize(450, 150);
    QIcon windowIcon(":/valute.png");
    setWindowIcon(windowIcon);
    Dollars=new QLineEdit(this);
    Uans=new QLineEdit(this);
    Euros=new QLineEdit(this);
    Dollars->setReadOnly(true);
    Uans->setReadOnly(true);
    Euros->setReadOnly(true);
    QFormLayout* layout2 = new QFormLayout();
    QLabel* label=new QLabel;
    QString date = QDate::currentDate().toString("dd.MM.yyyy");
    label->setText("Курс валют на " + date);
    layout2->addRow(label);
    layout2->addRow(Dollars);
    layout2->addRow(Uans);
    layout2->addRow(Euros);
    centralWidget->setLayout(layout2);
    sendData();
}

void Valutes::getResponse(QNetworkReply *reply)
{
    QDomDocument domDoc;

            if(domDoc.setContent(reply->readAll())) {
                QDomNode rootNode = domDoc.documentElement ();
                findNode(rootNode, "Valute", "R01235", Dollars);
                findNode(rootNode, "Valute", "R01375", Uans);
                findNode(rootNode, "Valute", "R01239", Euros);
            }
            delete reply;
}

void Valutes::sendData()
{
    QNetworkRequest request(QUrl("http://www.cbr.ru/scripts/XML_daily.asp"));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Valutes::getResponse);
    manager->get(QNetworkRequest(request));
}

bool Valutes::findNode(const QDomNode &node, const QString &Name, const QString &number, QLineEdit *line)
{
    if(node.isElement())
    {
        QDomElement element = node.toElement();
        if(element.tagName() == Name && element.attribute("ID") == number)
        {

            QString str;
            str.append(node.firstChildElement("CharCode").text());
            str.append(" ");
            str.append(node.firstChildElement("Name").text());
            str.append(" ");
            int nominal = node.firstChildElement("Nominal").text().toInt();
            QString str_double(node.firstChildElement("Value").text());
            str_double.replace(",",".");
            double res = str_double.toDouble();
            str.append(QString::number(res /qreal(nominal), 'f', 2));
            str.append("  руб");
            line->setText(str);

            return true;
        }

    }

    QDomNode siblingNode = node.nextSiblingElement();

    while(!siblingNode.isNull()){
        bool res = findNode( siblingNode, Name, number, line);
        if(res)
            return true;
        siblingNode = siblingNode.nextSiblingElement();
    }

    QDomNode childNode = node.firstChild();
    if(!childNode.isNull()){
        bool res = findNode( childNode, Name, number, line);
        if(res)
            return true;
    }

    return false;
}
