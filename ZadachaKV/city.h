#ifndef CITY_H
#define CITY_H

#include <QGraphicsItem>
#include <string>
#include <vector>
#include <QPainter>
#include <fstream>

class city : public QGraphicsItem
{
public:
    city(QGraphicsItem* parent = nullptr);
    city(QString, int, int, QGraphicsItem* parent = nullptr);
    city(const city&);
    QString name;
    friend bool operator== (const city&, const city&);
    void set_number(QString);
    void selected_color();
    void unselected_color();
    friend std::fstream &operator>>(std::fstream &fin, city &p);
    friend std::fstream &operator<<(std::fstream &fout, const city &p);

private:
    int pos_x;
    int pos_y;
    QString number;
    QColor color;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
};

#endif // CITY_H
