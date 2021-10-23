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
    char tipe='p';
    float friccion;

    Plataformas(float f);
    void Set_plataforma(int tipo, int bloque);

};

#endif // PLATAFORMAS_H
