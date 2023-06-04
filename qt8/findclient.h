#ifndef FINDCLIENT_H
#define FINDCLIENT_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

class findclient: public QDialog
{
    Q_OBJECT
public:
    explicit findclient(QWidget *parent=nullptr);
private:
    QPushButton *FConfirmBtn;
    QLineEdit *FIOLineFind;
    QLineEdit *PassportLineFind;
signals:
    void FindConfirmed(const QString&, const QString&);
private slots:
    void ConfirmFind();
};

#endif // FINDCLIENT_H
