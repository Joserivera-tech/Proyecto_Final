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
    bool vida=true, suelo=false, salto=true;
    float px=0,py=0,vx=0,vy=0,ay=0,ax=0;

public:
    Personaje(int x, int y);
    void getPos(QList<QGraphicsItem *> objetos, int tipe);
};

#endif // PERSONAJE_H
