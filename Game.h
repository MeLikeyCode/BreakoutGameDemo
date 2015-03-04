#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Game: public QGraphicsView{
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void start();
    void createBlockCol(double x);
    void creatBlockGrid();

    // public attributes
    QGraphicsScene* scene;

};

#endif // GAME_H
