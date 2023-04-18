#include <iostream>
#include <fstream>

using namespace std;

int nfilas;

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

void Horario(char* codigo,char* dias, char* hora){
    fstream archivo("horario.txt", ios::in | ios::out | ios::app); // Se abre el archivo en modo de lectura y escritura

        if (archivo.is_open()) { // Verificar si el archivo se abrió correctamente

                    archivo << codigo;
                    archivo <<';';
                    archivo << dias;
                    archivo <<';';
                    archivo << hora;
                    archivo <<';';
                    archivo <<endl;
                    // Se escribe en el archivo en la posición del cursor de escritura

                    archivo.close(); // Cerrar el archivo
        } else {
            cout << "No se pudo abrir el archivo." << endl;
        }



}
void leer(char f){
    int pos=0;
    ifstream archivo("archivo.txt");
    if(archivo.is_open()){
        char temp;
        while(archivo.get(temp)){
            if(temp == f){
                archivo.seekg(pos, ios::beg);
                        break;
            }
            pos++;
        }
        cout << pos<<endl;
        archivo.close();
    }
}



int main()
{
//cout<<"Numero de materias: ";
//cin >> nfilas;
leer(';');

}
