#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H

#define lado 16


#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>



class Plataformas: public QObject, public QGraphicsPixmapItem
{

private:
    QPixmap img;
    QPixmap sprites;
public:
    Plataformas(int ancho, int alto);
};

#endif // PLATAFORMAS_H
