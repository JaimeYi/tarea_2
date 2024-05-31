#include <fstream>
#include "def_funciones_superstring.cpp"

int main (){
    super_string superString;
    string hola, prueba;
    prueba = "lA";
    int largo = prueba.length();
    for (int i = 0; i < largo; i++){
        superString.agregar(prueba[i]);
    }
    superString.recortar();
    superString.printInOrder();
    return 0;
}