#include <fstream>
#include "def_funciones_superstring.cpp"

void mostrar(super_string& s){
    cout << s.stringizar() << endl;
}

void insertar(int i, string str, super_string& s){
    super_string a, b, nuevo;
    s.separar(i, a, b);
    int largo = str.length();
    for (int x = 0; x < largo; x++){
        nuevo.agregar(str[x]);
    }
    if (i == 0){
        nuevo.juntar(b);
        s = nuevo;
    } else {
    a.juntar(nuevo);
    a.juntar(b);
    s = a;
    }
}


int main (){
    super_string xd, m, ya, pr, s;
    string hola, prueba , ja;

    insertar(0, "Gato_", xd);
    mostrar(xd);
    insertar(5, "amarillo_", xd);
    mostrar(xd);

    return 0;
}