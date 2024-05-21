#include <fstream>
#include "def_funciones_superstring.cpp"

int main (){
    fstream file;
    file.open("prueba.txt");
    super_string superString;
    superString.agregar('H');
    superString.agregar('o');
    superString.agregar('l');
    superString.agregar('a');
    superString.imprimir();
    file.close();
    return 0;
}