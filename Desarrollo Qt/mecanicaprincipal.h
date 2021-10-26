#ifndef MECANICAPRINCIPAL_H
#define MECANICAPRINCIPAL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include <QVector>


class MecanicaPrincipal: public QObject, public QGraphicsPixmapItem
{
public:
    MecanicaPrincipal(QGraphicsScene *scene);
    void CrearZonas();

private:
    int dificultad=2;

    QVector<QGraphicsRectItem *> secciones;
    QGraphicsScene *escena;

};

#endif // MECANICAPRINCIPAL_H
