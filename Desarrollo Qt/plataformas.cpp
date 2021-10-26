#include "plataformas.h"

Plataformas::Plataformas(float f)
{
    sprites_fondo = QPixmap(":/img/Sprites_Plataformas.png");
    sprites = QPixmap(":/img/Sprites_Plataformas_2.png");
    setPixmap(img);
    friccion=f;
}

void Plataformas::Set_plataforma(int tipo, int bloque, bool fondo)
{
    if(fondo){
        if(tipo <=3){
            if(bloque==4) img = sprites_fondo.copy(0,1,1,1).scaled(16,16);
            else if(tipo == 3) img=sprites_fondo.copy(bloque*16,80,16,16);
            else img =sprites_fondo.copy(bloque*16,tipo*16,16,16);
            setPixmap(img.scaled(40,40));
        }
    }
    else{
        if(tipo <=3){
            if(bloque==4) img = sprites.copy(0,1,1,1).scaled(16,16);
            else if(tipo == 3) img=sprites.copy(bloque*16,80,16,16);
            else img =sprites.copy(bloque*16,tipo*16,16,16);
            setPixmap(img.scaled(40,40));
        }
    }
}


