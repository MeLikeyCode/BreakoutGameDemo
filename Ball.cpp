#include "Ball.h"
#include <QTimer>
#include <QBrush>
#include "Game.h"
#include "Paddle.h"
#include "Block.h"

extern Game* game;

Ball::Ball(QGraphicsItem *parent): QGraphicsRectItem(parent), QObject(){
    // draw rect
    setRect(0,0,50,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    // move up right initially
    xVelocity = 0;
    yVelocity = -5;

    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(15);
}

double Ball::getCenterX(){
    return x() + rect().width()/2;
}

void Ball::move(){
    // if out of bounds, reverse the velocity
    reverseVelocityIfOutOfBounds();

    // if collides with paddle, reverse yVelocity, and add xVelocity
    // depending on where (in the x axis) the ball hits the paddle
    handlePaddleCollision();

    // handle collisions with blocks (destroy blocks and reverse ball velocity)
    handleBlockCollision();

    moveBy(xVelocity,yVelocity);
}

void Ball::reverseVelocityIfOutOfBounds(){
    // check if out of bound, if so, reverse the proper velocity
    double screenW = game->width();
    double screenH = game->height();

    // left edge
    if (mapToScene(rect().topLeft()).x() <= 0){
        xVelocity = -1 * xVelocity;
    }

    // right edge
    if (mapToScene(rect().topRight()).x() >= screenW){
        xVelocity = -1 * xVelocity;
    }

    // top edge
    if (mapToScene(rect().topLeft()).y() <= 0){
        yVelocity = -1 * yVelocity;
    }

    // bottom edge - NONE (can fall through bottom)
}

void Ball::handlePaddleCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        Paddle* paddle = dynamic_cast<Paddle*>(cItems[i]);
        if (paddle){
            // collides with paddle

            // reverse the y velocity
            yVelocity = -1 * yVelocity;

            // add to x velocity depending on where it hits the paddle
            double ballX = getCenterX();
            double paddleX = paddle->getCenterX();

            double dvx = ballX - paddleX;
            xVelocity = (xVelocity + dvx)/15;

            return;
        }
    }
}

void Ball::handleBlockCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i){
        Block* block = dynamic_cast<Block*>(cItems[i]);
        // collides with block
        if (block){
            double yPad = 15;
            double xPad = 15;
            double ballx = pos().x();
            double bally = pos().y();
            double blockx = block->pos().x();
            double blocky = block->pos().y();

            // collides from bottom
            if (bally > blocky + yPad && yVelocity < 0){
                yVelocity = -1 * yVelocity;
            }

            // collides from top
            if (blocky > bally + yPad && yVelocity > 0 ){
                yVelocity = -1 * yVelocity;
            }

            // collides from right
            if (ballx > blockx + xPad && xVelocity < 0){
                xVelocity = -1 * xVelocity;
            }

            // collides from left
            if (blockx > ballx + xPad && xVelocity > 0){
                xVelocity = -1 * xVelocity;
            }

            // delete block(s)
            game->scene->removeItem(block);
            delete block;
        }
    }
}
