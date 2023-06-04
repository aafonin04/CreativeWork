#include "report.h"
#include "ui_Report.h"

Report::Report(QWidget* parent)
    : QWidget(parent),
      ui(new Ui::Report)
{
    ui->setupUi(this);
}
