#include <iostream>
#include <fstream>

using namespace std;

int nmaterias=0;
int codigos[10];
int HTP[10];
char horariomatriz[14][6];

void matrizcero(){
    for(int i=0;i<15;i++){
        for(int j=0;j<7;j++){
            horariomatriz[i][j]=' ';
        }
    }
}

void rellenarmatriz(int fila, char dia){
    if(dia == 'L'){
        horariomatriz[fila-6][0]='X';
        }
    else if(dia == 'M'){
        horariomatriz[fila-6][1]='X';

    }
    else if(dia == 'W'){
        horariomatriz[fila-6][2]='X';

    }
    else if(dia == 'J'){
        horariomatriz[fila-6][3]='X';

    }
    else if(dia == 'V'){
        horariomatriz[fila-6][4]='X';

    }
    else if(dia == 'S'){
        horariomatriz[fila-6][5]='X';

    }



}


void Cursos(){
   char* c= new char; //Declara un arreglo dinamico para almacenar temporalmente el dato ingresado

    ofstream archivo("archivo.txt", ios::app);
    if (archivo.is_open()) { // Verificar si el archivo se abrió correctamente
        cout <<"Ingrese codigo: ";
        cin >> c;
        archivo <<c << ";";
           cout<<"Ingrese Nombre: ";
           cin >> c;
           archivo << c <<";";

               cout<<"Ingrese Numero de Creditos: ";
               cin >> c;
               archivo << c <<";";
                   cout<<"Ingrese HTD: ";
                   cin >> c;
                   archivo << c <<";";

                    archivo <<endl;


       } else {
           cout << "No se pudo abrir el archivo." << endl;
       }
    archivo.close(); // Cerrar el archivo
    delete c;

}

void Horario(){
     char* c= new char;
    ofstream archivo("horario.txt",ios::out | ios::app); // Se abre el archivo en modo de lectura y escritura

        if (archivo.is_open()) { // Verificar si el archivo se abrió correctamente

            for(int i=0;i<nmaterias;i++){
                cout<<"Materia: "<<codigos[i]<<endl;
                archivo << codigos[i] << ";";
                cout<<"Ingrese horario XY0-0: ";
                cin >> c;
                archivo << c;

                archivo <<endl;
            }
                    // Se escribe en el archivo en la posición del cursor de escritura

                    archivo.close(); // Cerrar el archivo
        }
            else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        delete c;



}
int leer(){

    ifstream archivo("archivo.txt");
        if (archivo.is_open()) {
            nmaterias=0;
            char c;
            int num = 0, campo = 0, f=0, g=0;
            char nombre[20];
            int i = 0;//Recorre el nombre
            while (archivo.get(c)) {
                if (c == ';') {

                    campo++;
                    i = 0;
                } else if (c == '\n') {
                    codigos[f]=num; //Me guarda los codigos de cada materia
                    f++;
                    g++;
                    nmaterias++;

                    num = 0;
                    campo = 0;
                    i = 0;
                } else {
                    if (campo == 0) { //Convertimos a entero
                        num = num * 10 + (c - '0');


                    } else if (campo == 1) {
                        nombre[i++] = c;
                    }
                    else if (campo == 2){
                        int htp=((c-'0')*48)/16;
                        HTP[g]=htp;


                    }
                }
            }

            archivo.close();
        }

        else {
            cout << "Todavia no has registrado los cursos." << endl;
        }


return 0;
}

void leerHorario(){
    ifstream archivo("horario.txt");
        if (archivo.is_open()) {
            char c;
            int num = 0, campo = 0, f=0, hora[2]={0,0},count2=0;
            char Dias[2]={' ',' '};
            int i = 0;//Recorre el nombre
            while (archivo.get(c)) {
                if (c == ';') {
                    codigos[f]=num; //Me guarda los codigos de cada materia
                    f++;
                    campo++;
                    i = 0;
                    num = 0;
                } else if (c == '\n') {//Nueva linea para leer, reinician las variables

                    num = 0;
                    campo = 0;
                    i = 0;
                    f=0;
                    count2=0;

                    for(int i=0;i<2;i++){
                        for(int j = hora[0];j<=hora[1];j++){
                            rellenarmatriz(j,Dias[i]); //Guarda en la matriz los horarios ocupados
                       }
                   }


                } else if (c=='-'){
                    count2++;
                    num = 0;
                }
                else {
                    if (campo == 0) { //Convertimos a entero
                        num = num * 10 + (c - '0');
                    }
                    else if (campo == 1) {//Horario formato MJ8-10

                        if(i<2){
                        Dias[i]=c;
                        }
                        i++;
                        if(i>2){

                           num = num * 10 + (c - '0');
                           hora[count2]=num;

                           }


                    }

                }



            }

            archivo.close();
        }

        else {
            cout << "Error al abrir el archivo." << endl;
        }

}

void mostrarhorario(){
    cout<<"L M X J V S Hora"<<endl;
    for(int i=0;i<15;i++){

        for(int j=0;j<6;j++){

            cout<<horariomatriz[i][j]<<' ';
        }
        cout <<i+6<<":00"<<endl;

    }

}

int menu(){
    int x=0;
    cout <<"Que desea hacer ?"<<endl;
    cout <<"1. Registrar cursos."<<endl;
    cout <<"2. Registrar Horarios."<<endl;
    cout <<"3. Visualizar Horario."<<endl;
    cout <<"0. Salir."<<endl;
    cin >> x;
    return x;
}

int main()
{
matrizcero();
leer();
 //Esta funcion lee el archivo y guarda en un arreglo los codigos, en otro las horas de trabajo personal.
int x = 0;
do{
   x = menu();
    switch (x) {
    case 1:
        Cursos();
        leer();
        break;
    case 2:
        Horario();
        break;
    case 3:
        leerHorario();
        mostrarhorario();
        break;
    }
}while(x!=0);



//cout<<"Numero de materias: ";
//cin >> nmaterias;

//Horario();
//leerHorario();
//mostrarhorario();
}
