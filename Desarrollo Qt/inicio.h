#ifndef INICIO_H
#define INICIO_H

#include <QDialog>
#include <mainwindow.h>

#include <string>
#include <fstream>

namespace Ui {
class Inicio;
}

class Inicio : public QDialog
{
    Q_OBJECT

public:
    bool jugar=false; //si se esta jugando
    MainWindow *w; //la ventana de juego

    explicit Inicio(QWidget *parent = nullptr);
    ~Inicio();

private slots:
    //botones en el ui

    void on_Jugar_clicked();

    void on_Dificultad_valueChanged(int arg1);

    void on_signIn_clicked();

    void on_Registrar_clicked();

    void on_CargarPartida_clicked();

    void on_ShowScores_clicked();

private:
    Ui::Inicio *ui;
    string usr; // usuario
    string leer(string nombre, bool modo); //lectura de un archivo
    void GetUsers(string archivo, QVector<string> *users, bool show); //obtiene los usuarios y los guarda en users
    void registro_users(string archivo, string user, string pass, string puntaje); //escrie un nuevo usuario con su contraseña
    bool users_validation(string usr, string pass); // compara los datos ingresados por el usuario
};

#endif // INICIO_H
