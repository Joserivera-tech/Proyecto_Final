#include "mecanicaprincipal.h"
MecanicaPrincipal::MecanicaPrincipal(QGraphicsScene *scene)
{
    escena = scene;
}

void MecanicaPrincipal::CrearZonas()
{
    for(int i=0;i<dificultad;i++){
        for(int c=0;c<dificultad;c++){
            secciones.push_back(escena->addRect(0+(c*110),0+(i*110),100,100));
        }
    }
}
