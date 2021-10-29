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
    bool jugar=false;
    MainWindow *w;

    explicit Inicio(QWidget *parent = nullptr);
    ~Inicio();

private slots:
    void on_Jugar_clicked();

    void on_Dificultad_valueChanged(int arg1);

    void on_signIn_clicked();

    void on_Registrar_clicked();

    void on_CargarPartida_clicked();

    void on_ShowScores_clicked();

private:
    Ui::Inicio *ui;
    string usr;
    string leer(string nombre, bool modo);
    void GetUsers(string archivo, QVector<QVector<string>> *users);
    void registro_users(string archivo, string user, string pass, string saldo); //escribe
    bool users_validation(string usr, string pass);
};

#endif // INICIO_H
