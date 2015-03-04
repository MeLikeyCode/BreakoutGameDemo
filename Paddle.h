#ifndef PADDLE_H
#define PADDLE_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class Paddle: public QGraphicsRectItem{
public:
    // constructors
    Paddle(QGraphicsItem* parent=NULL);

    // public methods
    double getCenterX();

    // events
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
};

#endif // PADDLE_H
