#include <fstream>
#include "def_funciones_superstring.cpp"

int main (){
    super_string superString, xd;
    string hola, prueba , ja;
    prueba = "Shell";
    ja = "Power";
    int largo = prueba.length();
    for (int i = 0; i < largo; i++){
        superString.agregar(prueba[i]);
    }
    largo = ja.length();
    for (int i = 0; i < largo; i++){
        xd.agregar(ja[i]);
    }
    xd.limpiar();
    xd.agregar('J');
    hola = xd.stringizar();
    cout << hola << endl;
    return 0;
}