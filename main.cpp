#include <iostream>
#include <fstream>

using namespace std;

int nmaterias=0;
int tam=0;
int codigos[10];
int HTP[10];
char **nombres; // Filas: Nombres   Columnas: Letras de cada nombre.
int *v;



int horariomatriz[14][6];
//Funciones

void reservar_memoria(int tam_nombres, int i){

        nombres[i]=new char[tam_nombres];
    }



void contar_cursos(){
    ifstream archivo("archivo.txt");
        if (archivo.is_open()) {
            nmaterias=0;
            char* c = new char[3];
               while (archivo.get(*c)) {
                if (*c =='\n') {
                    nmaterias++;
                  }

                }
         }
}



void liberar_memoria(){
    for(int i=0;i<nmaterias;i++){
        delete[] nombres[i];
    }
    delete[] nombres;
}


void matrizcero(){
    for(int i=0;i<15;i++){
        for(int j=0;j<7;j++){
            horariomatriz[i][j]=0;
        }
    }
}

void rellenarmatriz(int fila, char dia,int codigo){ //Asigna los horarios a cada dia de cada curso
    if(dia == 'L'){
        horariomatriz[fila-6][0]=codigo;
        }
    else if(dia == 'M'){
        horariomatriz[fila-6][1]=codigo;

    }
    else if(dia == 'W'){
        horariomatriz[fila-6][2]=codigo;

    }
    else if(dia == 'J'){
        horariomatriz[fila-6][3]=codigo;

    }
    else if(dia == 'V'){
        horariomatriz[fila-6][4]=codigo;

    }
    else if(dia == 'S'){
        horariomatriz[fila-6][5]=codigo;

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
                   archivo << c;

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
                cout<<"Ingrese horario en formato DiaDiaHora1-Hora2: ";
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
int leerDatos(){ //Me lee el archivo para obtener los datos. Tambien guarda las horas de trabajo personal

    ifstream archivo("archivo.txt");
        if (archivo.is_open()) {

            char* c = new char[3]; //Arreglo auxiliar para leer los caracteres del archivo.
            char* aux = new char[20];//Arreglo auxiliar para guardar los nombres y luego copiarlos a la matriz.
            int num = 0, campo = 0, f=0, g=0, i=0; //Campo1|Campo2|Campo3|... se pueden añador más.
            tam=0;//Guarda el tamaño de cada nombre para luego asignar memoria de ese tamaño.

            while (archivo.get(*c)) {
                if (*c == ';') {

                    campo++;

                } else if (*c == '\n') {// Cada vez que hay un salto de linea es un dato nuevo, se reinicial las variables.
                    codigos[f]=num;
                    v[f]=i;// Almacena los tamaños de cada nombre para posteriormente acceder a ellos correctamente.
                    reservar_memoria(i,f); //Reserva memoria adecuada para almnacenar el nombre
                    for(int k=0;k<i;k++){
                        *(*(nombres+f)+k)=aux[k]; //Guarda letra a letra en la matriz de nombres, cada letra es una columna nueva, cada nombre es una fila.
                    }
                    f++;
                    g++;
                    num = 0;
                    campo = 0;
                    i = 0;
                } else {

                  if (campo == 0) { //Convertimos a entero
                        num = num * 10 + (*c - '0');
                } else if (campo == 1) {
                        aux[i++]=*c;
                        tam++;

                    }
                    else if (campo == 2){ // Calcula las horas de trabajo personal y las almacena en un arreglo.
                        int htp=((*c-'0')*48)/16;
                        HTP[g]=htp;

                    }
                }
            }

            archivo.close();
            delete[] c; //Se eliminan los arreglos auxiliares.
            delete[] aux;
        }

        else {
            cout << "Todavia no has registrado los cursos." << endl;
        }


return 0;
}

void leerHorario(){ // Me lee el archivo donde están los horarios de cada curso.
    ifstream archivo("horario.txt");
        if (archivo.is_open()) {
            char c;
            int num = 0, campo = 0, f=0, hora[2]={0,0},count2=0;
            char Dias[2]={' ',' '};
            int i = 0;//Recorre el nombre
            while (archivo.get(c)) {
                if (c == ';') {
                    codigos[f]=num; //Me guarda los codigos de cada materia

                    campo++;
                    i = 0;
                    num = 0;
                } else if (c == '\n') {//Nueva linea para leer, reinician las variables
                    f++;
                    num = 0;
                    campo = 0;
                    i = 0;
                    f=0;
                    count2=0;
                    if(hora[0]<6){break;}

                    for(int i=0;i<2;i++){
                        for(int j = hora[0];j<=hora[1];j++){
                            rellenarmatriz(j,Dias[i],codigos[f]); //Guarda en la matriz los horarios ocupados
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
    cout<<"|   L   ||   M   ||   W   ||   J   ||   V   ||   S   ||   H    "<<endl;
    for(int i=0;i<15;i++){

        for(int j=0;j<6;j++){
            if(horariomatriz[i][j]==0){
                cout<<"|_______|";
            }else {

              cout<<"|"<<horariomatriz[i][j]<<"|";

            }


        }
        cout <<"   " <<i+6<<":00"<<endl;

    }

}
void ver_cursos(){
    for(int i=0;i<nmaterias;i++){
        for(int j=0;j<v[i];j++){
            cout<<*(*(nombres+i)+j);
        }
        cout<<" Codigo: "<<codigos[i]<<"| HTP: "<<HTP[i]<<endl<<endl;
    }
}

int menu(){
    int x=0;
    cout <<"Que desea hacer ?"<<endl;
    cout <<"1. Registrar cursos."<<endl;
    cout <<"2. Registrar Horarios."<<endl;
    cout <<"3. Visualizar Horario."<<endl;
    cout <<"4. Ver Cursos."<<endl;
    cout <<"0. Salir."<<endl;
    cin >> x;
    return x;
}

int main()
{


contar_cursos(); // Obtiene el numero de cursos registrados.
v = new int[nmaterias];
nombres = new char*[nmaterias];
matrizcero();// Limpia la matriz donde se visualiza el horario
leerDatos();// Adquiere los datos


int x = 0;
do{
   x = menu();
    switch (x) {
    case 1: //Registrar Cursos
        Cursos();
        leerDatos();
        break;
    case 2: //Registrar Horarios
        leerDatos();
        Horario();
        break;
    case 3: //Visualizar Horario
        leerHorario();
        mostrarhorario();
        break;
    case 4:
        leerDatos();
        ver_cursos();

        break;
    }
}while(x!=0);

delete [] v;
liberar_memoria();




}
