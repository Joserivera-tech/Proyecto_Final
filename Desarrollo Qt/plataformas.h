#ifndef PLATAFORMAS_H
#define PLATAFORMAS_H

#define lado 16


#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QObject>

class Plataformas: public QObject, public QGraphicsPixmapItem
{
private:
    int C=0;

    QPixmap img;
    QPixmap sprites_fondo, sprites;


public:
    int tipe, px=0;

    Plataformas();
    void Set_plataforma(int tipo, int bloque, bool fondo);
    void Contraer();

};

#endif // PLATAFORMAS_H
