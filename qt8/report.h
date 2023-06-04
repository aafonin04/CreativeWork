#ifndef REPORT_H
#define REPORT_H

#include <QWidget>

namespace Ui{class Report;}

class Report: public QWidget
{
    Q_OBJECT
public:
     Report(QWidget* parent=nullptr);
    ~Report();
};

#endif // REPORT_H
