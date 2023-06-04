#include "matrixdialog.h"
#include "ui_matrixdialog.h"
#include <QHeaderView>
#include <QVBoxLayout>

MatrixDialog::MatrixDialog(const std::vector<std::vector<double>>& adjacencyMatrix, QWidget* parent)
    : QDialog(parent), ui(new Ui::MatrixDialog), adjacencyMatrix(adjacencyMatrix)
{
    ui->setupUi(this);
    setupMatrixTable();
    setMatrixData();
}

void MatrixDialog::setupMatrixTable()
{
    matrixTable = new QTableWidget(this);
        matrixTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        matrixTable->setSelectionMode(QAbstractItemView::NoSelection);
        matrixTable->verticalHeader()->setVisible(true);  // Устанавливаем видимость вертикального заголовка
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(matrixTable);
        setLayout(layout);
}

void MatrixDialog::setMatrixData()
{
    int rowCount = adjacencyMatrix.size();
    int columnCount = adjacencyMatrix[0].size();

    matrixTable->setRowCount(rowCount);
    matrixTable->setColumnCount(columnCount);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < columnCount; j++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(adjacencyMatrix[i][j]));
            matrixTable->setItem(i, j, item);
        }
    }
}

MatrixDialog::~MatrixDialog()
{
    delete ui;
}
