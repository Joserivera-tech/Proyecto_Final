#include "inicio.h"
#include "ui_inicio.h"

Inicio::Inicio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inicio)
{
    ui->setupUi(this);
    ui->Puntaje->setReadOnly(true);

    setWindowIcon(QPixmap(":/img/logo.png"));
}

Inicio::~Inicio()
{
    delete ui;
    w->~MainWindow();
}

void Inicio::on_Jugar_clicked()
{
    if(w==nullptr){
        w=new MainWindow(usr);
    }
    w->dificult=ui->Dificultad->value()-1;
    w->show();
    w->Iniciar(0);
}
void Inicio::on_Dificultad_valueChanged(int arg1)
{
    if(arg1<=3 && arg1>0){
        ui->Jugar->setEnabled(true);
    }
    else{
        ui->Jugar->setEnabled(false);

    }
}

void Inicio::on_signIn_clicked()
{
    fstream archivo;
    string name="";
    if(users_validation((ui->Nombre->toPlainText()).toStdString(),(ui->Contrasena->toPlainText()).toStdString())){
        ui->resultado->setText("Inicio correcto");
        ui->Dificultad->setEnabled(true);
        usr=ui->Nombre->toPlainText().toStdString();
        name+=usr+".txt";
        archivo.open(name);
        if(archivo.is_open()){
            ui->CargarPartida->setEnabled(true);
        }
        archivo.close();
    }
    else{
        ui->resultado->setText("Usuario Invalido");
        ui->CargarPartida->setEnabled(false);
    }
}
void Inicio::on_Registrar_clicked()
{
    if(ui->password->toPlainText()==ui->Cpassword->toPlainText()){
        registro_users("users.txt",ui->name->toPlainText().toStdString(),ui->password->toPlainText().toStdString(),"0");
    }

}

string Inicio::leer(string nombre, bool modo)
{
    string datos;
    fstream text;
    unsigned long long dtam;
    if(modo){
        fstream text(nombre, fstream::in);
        if(text.is_open()){
            while(!text.eof())datos.push_back(text.get());
            datos.pop_back();
        }
        else cout<<"El archivo no pudo ser abierto"<<endl;
    }
    else{
        text.open(nombre, fstream::in | fstream::binary | fstream::ate);
        if(text.is_open()){
            dtam=text.tellg();
            text.seekg(0);
            for(unsigned long long i=0; i<tam; i++) datos.push_back(text.get());
        }
        else cout<<"El archivo no pudo ser abierto"<<endl;
    }
    text.close();
    return datos;
}

void Inicio::GetUsers(string archivo, QVector<QVector<string>> *users)
{
    fstream arch(archivo);
    string linea, dato, arreglo[3], datos="Score:\n", valores[2];
    size_t pos;
    int contador =0;
    while(!arch.eof()){
        getline(arch,linea);
        while ((pos = linea.find(",")) != std::string::npos){

            dato = linea.substr(0, pos);
            arreglo[contador]=dato;
            linea.erase(0, pos + 1);
            contador++;
        }
        if(arreglo[0].size()>3) datos+=arreglo[0]+":  "+arreglo[2]+"\n";
        arreglo[0]="";
        arreglo[1]="";
        arreglo[2]="";
        contador=0;
    }
    ui->Puntaje->setPlainText(QString::fromStdString(datos));
}


void Inicio::registro_users(string archivo, string user, string pass, string saldo)
{
    string separador=",";
    fstream text(archivo, fstream::app);

    text << user;
    text << separador;
    text << pass;
    text << separador;
    text << saldo;
    text << separador;
    text << "\n";

    text.close();
    ui->resultado->setText("Resgitro exitoso");
}

bool Inicio::users_validation(string usr, string pass)
{
    ifstream archivo("users.txt");
    string linea,dato,arreglo[2];
    int fin=0,contador=0;
    size_t pos;//es un valor indefinido
    bool validacion=false;

    while(getline(archivo,linea)&&fin==0){/*Este bucle se repetira mientras la funcion getline pueda obtener
    lineas nuevas del archivo txt y la variable fin valga 0*/

        while ((pos = linea.find(",")) != std::string::npos){/* Si el valor devuelto por la funcion find es distinto a la constante npos esto
        significa que si se ha encontrado lo que se busca dentro de la variable linea */

            dato = linea.substr(0, pos);// Separamos los caracteres desde la posicion 0 hasta una posicion previa al caracter separador que es la coma

            arreglo[contador]=dato;// Guardamos el dato anterior dentro de la casilla 0 o la 1 dependiendo del valor de contador

            linea.erase(0, pos + 1);/*Eliminamos los caracteres desde la posicion 0 hasta la posicion donde
            se encuentra el caracter separador coma,incluida la coma*/

            contador++;// Aumentamos el valor del contador
        }

    if (arreglo[0].find(usr, 0) != string::npos){
        fin=1;/* Si el nombre de alguna linea es igual al ingresado por el usuario cambiamos el valor de la variable fin para que se
        termine el bucle, sin importar que la contraseña sea incorrecta */
    }
    contador=0;/* Regresamos el valor del contador a 0 por si en la línea previa no estuviesen el nombre y la contraseña de nuestro usuario, así
    continuamos en el bucle buscando hasta que se encuentre o se acaben los datos en el archivo de texto.*/
    }

    /* Revisamos a continuacion si el nombre de usuario y la contraseña son iguales a los ingresados por el usuario de ser asi le dejamos pasar,
       le damos un mensaje de bienvenida y realizamos cualquier otra accion que necesitemos*/
    if (usr==arreglo[0]&&pass==arreglo[1]){
        validacion=true;
    }

    else{
         ui->resultado->setText("Los datos ingresados son incorrectos");
    }

    return validacion;
}

void Inicio::on_CargarPartida_clicked()
{
    if(w ==nullptr){
        w=new MainWindow(usr);
    }
    string linea, dato, arreglo[3], name="";
    name += usr+".txt";

    ifstream archivo(name);

    int contador =0;
    while(contador<=5){
        archivo >> linea;
        if(contador==0 )w->punt=stoi(linea);
        else if(contador==1 )w->player->px=stoi(linea);
        else if(contador==2 )w->player->py=stoi(linea);
        else if(contador==3 )w->player->vx=stoi(linea);
        else if(contador==4 )w->player->vy=stoi(linea);
        else w->dificult = stoi(linea);
        contador++;
    }
    archivo.close();
    w->show();
    w->Iniciar(241800*w->punt/100);

}

void Inicio::on_ShowScores_clicked()
{
    QVector<QVector<string>> u;
    GetUsers("users.txt",&u);
}
