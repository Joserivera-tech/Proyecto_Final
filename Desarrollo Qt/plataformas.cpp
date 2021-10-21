#include "plataformas.h"

Plataformas::Plataformas(int ancho, int alto)
{
    sprites = QPixmap(":/img/Sprites_Plataformas.png");
    img = QPixmap(ancho*lado,alto*lado).scaled(40,40);
    img.fill(QColor(50,50,50));
}
