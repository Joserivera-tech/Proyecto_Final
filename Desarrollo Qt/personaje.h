#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsView>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>


class Personaje : public QObject, public QGraphicsPixmapItem
{
private:
    QPixmap Person, Default;
    int px=0,py=0;
    float ay=0,ax=0;
    bool ComprobarCollision(QRect rect1,QRect rect2);


public:
    QRect *pies;
    int vx=0,vy=0;
    bool vida=true, suelo=false, Salto=false;
    Personaje(int x, int y);
    void getPos(QList<QGraphicsItem *> objetos, int tipe);
};

#endif // PERSONAJE_H
