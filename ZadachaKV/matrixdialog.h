#ifndef MATRIXDIALOG_H
#define MATRIXDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class MatrixDialog;
}

class MatrixDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MatrixDialog(const std::vector<std::vector<double>>& adjacencyMatrix, QWidget* parent = nullptr);
    ~MatrixDialog();

private:
    Ui::MatrixDialog *ui;
    std::vector<std::vector<double>> adjacencyMatrix;
    QTableWidget* matrixTable;
    void setupMatrixTable();
    void setMatrixData();
};

#endif // MATRIXDIALOG_H
