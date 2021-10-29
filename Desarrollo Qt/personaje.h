#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsView>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

#include "plataformas.h"


class Personaje : public QObject, public QGraphicsPixmapItem
{
private:
    QPixmap Person, Default;
    QList<Plataformas *> Plat, PTramp;
    float ay=0,ax=0;
    bool ComprobarCollision(QRect rect1,QRect rect2);


public:
    int px=0,py=0, vx=0,vy=0;
    bool vida=true, suelo=false, Salto=false;
    Personaje(int x, int y,QList<Plataformas *> P , QList<Plataformas *> tromp);
    void getPos(QList<QGraphicsItem *> objetos, int tipe, int tipeD, int time);
    void setImage();
};

#endif // PERSONAJE_H
