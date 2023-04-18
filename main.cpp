#include <iostream>
#include <fstream>

using namespace std;

int nmaterias=0;
int codigos[10];
bool horariomatriz[14][6];

void matrizcero(){
    for(int i=0;i<15;i++){
        for(int j=0;j<7;j++){
            horariomatriz[i][j]=0;
        }
    }
}

void rellenarmatriz(int fila, char dia){
    if(dia == 'L'){
        horariomatriz[fila-6][0]=1;
        }
    else if(dia == 'M'){
        horariomatriz[fila-6][1]=1;

    }
    else if(dia == 'X'){
        horariomatriz[fila-6][2]=1;

    }
    else if(dia == 'J'){
        horariomatriz[fila-6][3]=1;

    }
    else if(dia == 'V'){
        horariomatriz[fila-6][4]=1;

    }
    else if(dia == 'S'){
        horariomatriz[fila-6][5]=1;

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

               cout<<"Ingrese HTD: ";
               cin >> c;
               archivo << c <<";";
                   cout<<"Ingrese Numero de creditos: ";
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
    fstream archivo("horario.txt", ios::in | ios::out | ios::app); // Se abre el archivo en modo de lectura y escritura

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
            char c;
            int num = 0, campo = 0, f=0;
            char nombre[20];
            int i = 0;//Recorre el nombre
            while (archivo.get(c)) {
                if (c == ';') {
                    codigos[f]=num; //Me guarda los codigos de cada materia
                    f++;
                    campo++;
                    i = 0;
                } else if (c == '\n') {

                    num = 0;
                    campo = 0;
                    i = 0;
                } else {
                    if (campo == 0) { //Convertimos a entero
                        num = num * 10 + (c - '0');


                    } else if (campo == 1) {
                        nombre[i++] = c;
                    }
                }
            }

            archivo.close();
        }

        else {
            cout << "Error al abrir el archivo." << endl;
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
                        for(int j=0;j<2;j++){
                            rellenarmatriz(hora[j],Dias[i]); //Guarda en la matriz los horarios ocupados
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
    cout<<"L M X J V S"<<endl;
    for(int i=0;i<15;i++){

        for(int j=0;j<6;j++){

            cout<<horariomatriz[i][j]<<' ';
        }
        cout <<"Hora: "<<i+6<<":00"<<endl;

    }

}


int main()
{
matrizcero();
//cout<<"Numero de materias: ";
//cin >> nmaterias;
//leer();
//Horario();
leerHorario();
mostrarhorario();
}
