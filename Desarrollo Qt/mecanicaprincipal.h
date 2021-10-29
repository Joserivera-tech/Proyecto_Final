#ifndef MECANICAPRINCIPAL_H
#define MECANICAPRINCIPAL_H

#include <QTimer>
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QVector>
#include <QMediaPlayer>
#include <Qthread>
#include <iostream>

using namespace std;

class MecanicaPrincipal: public QObject
{
    Q_OBJECT
public slots:
    void CambiarZonas();
    void AcZonasPeligro();
public:
    QVector<QGraphicsRectItem *> secciones;
    QMediaPlayer *reproductor;
    QTimer *TiempoMusica, *zonasPeligro;
    QVector<int> Zonas;
    int tiempo=0, tzonas=0;

    MecanicaPrincipal(QGraphicsScene *scene);
    ~MecanicaPrincipal();
    void CrearZonas();
    void IniciarJuego();
    int aleatorio(int a, int b);
    void showZonas();
    void hideZonas();
    void setDificultad(unsigned int d);
    void setPos(long p);

private:
    QGraphicsScene *escena;

    unsigned int difs[3][3]={{4,1000,1000},{6,800,1000},{6,700,1000}};
    unsigned int dificultad=0;
};

#endif // MECANICAPRINCIPAL_H
