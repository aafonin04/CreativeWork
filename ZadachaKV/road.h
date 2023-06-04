#ifndef ROAD_H
#define ROAD_H

#include <QGraphicsItem>
#include "city.h"
#include <fstream>

class road : public QGraphicsItem
{
public:
    road(city*, city*, double, QGraphicsItem* parent = nullptr);
    road(const road&);
    city* first_city;
    city* second_city;
    double length;
    friend bool operator== (const road&, const road&);
    void selected_color();
    void unselected_color();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    QString double_to_str(double);
    QColor color;

};

#endif // ROAD_H
