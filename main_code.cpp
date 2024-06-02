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
    fstream file;
    super_string s;
    string str, line;
    int i, j;
    file.open("prueba.txt");

    while(true){
        file >> line;

        if (line == "INSERTAR"){
            file >> i;
            file >> str;
            insertar(i, str, s);
        } else if (line == "MOSTRAR"){
            mostrar(s);
        }else if (line == "FIN"){
            break;
        } else if (line == "ELIMINAR"){
            file >> i;
            file >> j;
            eliminar(s, i, j);
        } else if (line == "RECORTAR"){
            recorte(s);
        } else if (line == "REVERSO"){
            file >> i;
            file >> j;
            reverse(s, i, j);
        }
    }

    return 0;
}