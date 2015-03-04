#include "Block.h"
#include <QBrush>

Block::Block(QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw rect
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::blue);
    setBrush(brush);
}
