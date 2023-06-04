#ifndef SOLUTION_H
#define SOLUTION_H

#include <QDialog>
#include <vector>
#include "city.h"
#include "road.h"
#include "matrixdialog.h"

namespace Ui {
class solution;
}

class solution : public QDialog
{
    Q_OBJECT

public:
    explicit solution(std::vector<city*>, std::vector<road*>,
                      QString, QWidget *parent = nullptr);
    ~solution();
    void return_solution();
signals:
    void solved(std::vector<int>);
private slots:
    void on_matrixbtn_clicked();
private:
    std::vector<int> solve(std::vector<std::vector<double>>, int);
    QString double_to_str(double);
    void print_matrix(std::vector<std::vector<double>>, int);
private:
    Ui::solution *ui;
    std::vector<QString> city_names;
    std::vector<std::vector<double>> matrix;
    std::vector<int> route;
    QString solution_text;
    MatrixDialog* matrixDialog;

};

#endif // SOLUTION_H
