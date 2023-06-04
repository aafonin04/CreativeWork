#include "city.h"

city::city(QGraphicsItem* parent): QGraphicsItem(parent) {
    name = "";
    pos_x = 0;
    pos_y = 0;
    color = Qt::cyan;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    number = "";
}

city::city(QString n, int x, int y, QGraphicsItem* parent) : QGraphicsItem(parent) {
    name = n;
    pos_x = x;
    pos_y = y;
    color = Qt::cyan;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    number = "";
}

city::city(const city& c){
    name = c.name;
    pos_x = c.pos_x;
    pos_y = c.pos_y;
    color = Qt::blue;
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    number = "";
}

QRectF city::boundingRect() const {
    return QRectF(pos_x, pos_y, 50, 50);
}

void city::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(color);
    painter->drawEllipse(0, 0, 50, 50);
    QFontMetrics fm(painter->font());
    int tw = fm.width(name);
    painter->drawText(25 - tw/2, 30, name);
    tw = fm.width(number);
    painter->drawText(25 - tw/2, -5, number);
}

void city::set_number(QString n) {
    number = n;
}

void city::selected_color() {
    color = Qt::green;
}

void city::unselected_color() {
    color = Qt::cyan;
}

bool operator== (const city &c1, const city &c2) {
    return c1.name == c2.name;
}

std::fstream &operator<<(std::fstream &fout, const city &c) {
    fout << '\n' << c.name.toStdString() <<
            '\n' << c.pos().x() << '\n' << c.pos().y() << '\n';
    return fout;
}

std::fstream &operator>>(std::fstream &fin, city &c) {
    std::string name;
    fin >> name;
    c.name = QString::fromStdString(name);
    int x, y;
    fin >> x; fin >> y;
    c.moveBy(x, y);
    return fin;
}
