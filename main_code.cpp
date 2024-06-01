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

void reverse(super_string& s, int l, int r){
    super_string a, b, c, d;
    string aux = s.stringizar();
    int largo = aux.length();
    if (l == 0 && r == largo-1){
        s.reverso();
    } else if (r == largo-1){
        s.separar(l, a, b);
        b.reverso();
        a.juntar(b);
        s = a;
    } else {
        s.separar(l, a, b);
        b.separar((r-l), c, d);
        c.reverso();
        a.juntar(c);
        a.juntar(d);
        s = a;
    }
}

void eliminar(super_string& s, int l, int r){
    super_string a, b, c ,d;
    string aux = s.stringizar();
    int largo = aux.length();
    if (l == 0 && r == largo-1){
        s.limpiar();
    } else if (r == largo-1){
        s.separar(l, a, b);
        s = a;
    } else {
        s.separar(l, a, b);
        b.separar((r-l), c, d);
        a.juntar(d);
        s = a;
    }
}

void recorte(super_string& s){
    int i = s.recortar();
    cout << i << endl;
}

int main (){
    super_string xd, m, ya, pr, s;
    string hola, prueba , ja;

    insertar(0, "El_Carlos", xd);
    mostrar(xd);
    insertar(9, "_es_malo", xd);
    mostrar(xd);
    eliminar(xd, 13, 16);
    mostrar(xd);
    insertar(13, "bueno", xd);
    mostrar(xd);
    recorte(xd);
    reverse(xd, 0, 17);
    mostrar(xd);
    recorte(xd);

    return 0;
}