#include "plataformas.h"

Plataformas::Plataformas()
{
    sprites_fondo = QPixmap(":/img/Sprites_Plataformas.png");
    sprites = QPixmap(":/img/Sprites_Plataformas_2.png");
    setPixmap(img);
}

void Plataformas::Set_plataforma(int tipo, int bloque, bool fondo)
{
    if(fondo){
        if(tipo <=6){
            if(bloque==4) img = sprites_fondo.copy(0,1,1,1).scaled(16,16).scaled(40,40);
            else if(tipo == 3) img=sprites_fondo.copy(bloque*16,80,16,16).scaled(40,40);
            else if(tipo==6) img =sprites_fondo.copy(bloque*16,tipo*16,16,16).scaledToWidth(40);
            else img =sprites_fondo.copy(bloque*16,tipo*16,16,16).scaled(40,40);
            setPixmap(img);
        }
    }
    else{
        if(tipo <=6){
            if(bloque==4) img = sprites.copy(0,1,1,1).scaled(16,16);
            else if(tipo == 3) img=sprites.copy(bloque*16,80,16,16);
            else if(tipo==6) img =sprites.copy(bloque*16,tipo*16,16,16).scaledToWidth(40);
            else img =sprites.copy(bloque*16,tipo*16,16,16);
            setPixmap(img);
        }
    }
}

void Plataformas::Contraer()
{
    C++;
    if(C>2){
        img =sprites.copy((C-2)*16,6*16,16,16);
        setPixmap(img.scaled(40,40));
        C=0;
    }
    else{
        img =sprites.copy(C*16,6*16,16,16);
        setPixmap(img.scaled(40,40));
    }
    if(px>=15) img =sprites.copy(1*16,6*16,16,16);
    else if(px>=30) img =sprites.copy(0*16,6*16,16,16);

}


