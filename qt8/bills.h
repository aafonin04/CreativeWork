#ifndef BILLS_H
#define BILLS_H

#include <QWidget>

namespace Ui {
class Bills;
}

class Bills : public QWidget
{
    Q_OBJECT

public:
    explicit Bills(QWidget *parent = nullptr);
    ~Bills();

private:
    Ui::Bills *ui;
};

#endif // BILLS_H
