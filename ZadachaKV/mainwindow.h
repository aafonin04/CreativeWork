#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "city.h"
#include <QGraphicsView>
#include <vector>
#include "road.h"
#include "mygraphicsscene.h"
#include <QKeyEvent>
#include "solution.h"
#include <QDoubleValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void add_city();
    void start_road_creation1();
    void choose_city(city*);
    void showSolution();
    void city_numeration(std::vector<int>);
    void process_selection(QGraphicsItem*);

protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::MainWindow *ui;
    myGraphicsScene* scene;
    std::vector<city*> cities;
    std::vector<road*> roads;
    city* chosen_city;
    solution* dialog;
    QDoubleValidator m_doubleValidator;
    bool double_sided;

};
#endif // MAINWINDOW_H
