#include "solution.h"
#include "ui_solution.h"
#include <algorithm>
#include <QFileDialog>
#include <QtMath>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QVBoxLayout>

solution::solution(std::vector<city*> cities, std::vector<road*> roads, QString starting_city, QWidget *parent): QDialog(parent),
    ui(new Ui::solution)
{
    ui->setupUi(this);
    int n = 0;
    for (auto i : cities) {
        city_names.push_back(i->name);
        matrix.emplace_back();
        for (int j = 0; j < n; ++j) {
            matrix[n].push_back(-1);
        }
        for (int j = 0; j < n + 1; ++j) {
            matrix[j].push_back(-1);
        }
        ++n;
    }
    for (auto i : roads) {
        int first_city_index = std::distance(city_names.begin(),
                                             std::find(city_names.begin(),
                                                       city_names.end(),
                                                       i->first_city->name));
        int second_city_index = std::distance(city_names.begin(),
                                             std::find(city_names.begin(),
                                                       city_names.end(),
                                                       i->second_city->name));
        matrix[first_city_index][second_city_index] = i->length;
    }
    int starting_city_index = std::distance(city_names.begin(),
                                                                    std::find(city_names.begin(),
                                                                              city_names.end(),
                                                                              starting_city));
    route = solve(matrix, starting_city_index);
    QString answer;
    if (route.size() == city_names.size()+1) {
        for (auto i : route) {
            answer += city_names[i] + "->";
        }
        answer.resize(answer.size() - 2);
        double length = 0;
        int last_city = route[0];
        for (auto it = ++route.begin(); it != route.end(); it++) {
            length += matrix[last_city][*it];
            last_city = *it;
        }
        answer += ". Длина всего пути: " + double_to_str(length);
        solution_text += "\nПолученный маршрут:" + answer;
    } else {
        solution_text += "\nПосещаный не все города => искомого пути не существует.";
        answer = "Нет такого пути!";
    }
    ui->answerLable->setText(ui->answerLable->text() + ' ' + answer);
}

QString solution::double_to_str(double in){
    QString result = QString::fromStdString(std::to_string(in));
    double intpart;
    while (result.back() == '0'){
        result.remove(result.length() - 1, 1);
    }
    if (modf(in, &intpart) == 0.0){
        result.remove(result.length() - 1, 1);
    }
    return result;
}

std::vector<int> solution::solve(std::vector<std::vector<double>> matrix,
                                 int starting_city){
    std::vector<std::pair<int, int>> branches;
    std::vector<int> route;
    matrix.emplace_back();
    for (int i = 0; i < matrix.size() - 1; ++i) {
        matrix[i].emplace_back();
        matrix[matrix.size() - 1].emplace_back();
    }
    matrix[matrix.size() - 1].push_back(-1);
    while (branches.size() < matrix.size() - 1) {
        for (int i = 0; i < matrix.size() - 1; ++i) {
            double min = INFINITY;
            for (int j = 0; j < matrix.size() - 1; ++j) {
                if (matrix[i][j] != -1 && matrix[i][j] < min) {
                    min = matrix[i][j];
                }
            }
            matrix[i][matrix.size() - 1] = min;
        }
        for (int i = 0; i < matrix.size() - 1; ++i) {
            for (int j = 0; j < matrix.size() - 1; ++j) {
                if (matrix[i][j] != -1) {
                    matrix[i][j] -= matrix[i][matrix.size() - 1];
                }
            }
        }
        for (int i = 0; i < matrix.size() - 1; ++i) {
            double min = INFINITY;
            for (int j = 0; j < matrix.size() - 1; ++j) {
                if (matrix[j][i] != -1 && matrix[j][i] < min) {
                    min = matrix[j][i];
                }
            }
            matrix[matrix.size() - 1][i] = min;
        }
        for (int i = 0; i < matrix.size() - 1; ++i) {
            for (int j = 0; j < matrix.size() - 1; ++j) {
                if (matrix[j][i] != -1) {
                    matrix[j][i] -= matrix[matrix.size() - 1][i];
                }
            }
        }
        std::pair<int, int> branch;
        double max_sum = -1;
        for (int i = 0; i < matrix.size() - 1; ++i) {
            for (int j = 0; j < matrix.size() - 1; ++j) {
                if (matrix[i][j] == 0) {
                    double min_row = INFINITY, min_column = INFINITY;
                    for (int k = 0; k < matrix.size() - 1; ++k) {
                        if (matrix[i][k] != -1 && k != j && matrix[i][k] < min_row) {
                            min_row = matrix[i][k];
                        }
                        if (matrix[k][j] != -1 && k != i && matrix[k][j] < min_column) {
                            min_column = matrix[k][j];
                        }
                    }
                    if (min_row + min_column > max_sum) {
                        branch.first = i;
                        branch.second = j;
                        max_sum = min_row + min_column;
                    }
                }
            }
        }
        for (int i = 0; i < matrix.size() - 1; ++i) {
            matrix[branch.first][i] = -1;
            matrix[i][branch.second] = -1;
        }
        matrix[branch.first][branch.second] = -1;
        matrix[branch.second][branch.first] = -1;
        branches.push_back(branch);

    }
    route.push_back(starting_city);
    for (int i = 0; i < matrix.size() - 1; ++i) {
        for (int j = 0; j < matrix.size() - 1; ++j) {
            if (branches[j].first == route.back()) {
                route.push_back(branches[j].second);
                break;
            }
        }
    }
    return route;
}


solution::~solution()
{
    delete ui;
}


void solution::on_matrixbtn_clicked()
{
   // Создаем диалоговое окно MatrixDialog
   MatrixDialog* matrixDialog = new MatrixDialog(matrix, this);
   // Показываем диалоговое окно
   matrixDialog->exec();
}
