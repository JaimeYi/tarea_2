#include <fstream>
#include "def_funciones_superstring.cpp"

/*****
* void mostrar
******
* convierte el super string dado en string usando el metodo 'stringizar' e imprime en pantalla este string
******
* Input:
* super_string& s : super_string a mostrar
* Returns:
* void, no retorna nada
*****/

void mostrar(super_string& s){
    cout << s.stringizar() << endl;
}

/*****
* void insertar
******
* esta función convierte un string dado como parametro en super string, luego separa el super string dado
* en la posición indicada, de esta forma se van a tener 3 super strings (a, b, nuevo), ya teniendo estos
* para mantener el orden se juntaran en el orden: a->nuevo, a->b. Y en caso de tener que hacer la 
* inserción al inicio del super string se juntara solo nuevo->b. 
******
* Input:
* int i : posición donde se realizara la división del super string
* string str : string que se convertira en super string y se juntara al super string s
* super_string& s : super string al que se unira el nuevo string
* Returns:
* void, no retorna nada
*****/

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

/*****
* void reverse
******
* esta funcion crea 3 super strings (menos cuando se reversa todo el super string, cuando
* se reversa de cierta posición hasta el final o cuando se reversa desde el inicio hasta 
* el final) donde reversa el super string central y despues vuelve a unirlos todos
******
* Input:
* super_string& s : super string donde se trabajara en la función
* int l : indice desde donde se reversara el super string
* int r : indice hasta donde se reversara el super string
******
* Returns:
* void, no retorna nada
*****/

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
    } else if(l == 0){
        s.separar(r, a, b);
        a.reverso();
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

/*****
* void eliminar
******
* esta funcion crea 3 super strings (menos cuando se elimina todo el super string, cuando
* se elimina de cierta posición hasta el final o cuando se elimina desde el inicio hasta 
* el final) donde se elimina el super string central y se juntan los dos restantes
******
* Input:
* super_string& s : super string donde se trabajara en la función
* int l : indice desde donde se eliminara el super string
* int r : indice hasta donde se eliminara el super string
******
* Returns:
* void, no retorna nada
*****/

void eliminar(super_string& s, int l, int r){
    super_string a, b, c ,d;
    string aux = s.stringizar();
    int largo = aux.length();
    if (l == 0 && r == largo-1){
        s.limpiar();
    } else if (r == largo-1){
        s.separar(l, a, b);
        s = a;
    } else if (l == 0){
        s.separar(r, a, b);
        s = b;
    } else {
        s.separar(l, a, b);
        b.separar((r-l), c, d);
        a.juntar(d);
        s = a;
    }
}

/*****
* void recorte
******
* esta función reduce el costo operacional del camino más largo de O(n) a 
* O(log n) mediante el uso del metodo recortar, luego de realizar esta 
* operación se imprime el nuevo alto del arbol en pantalla
******
* Input:
* super_string& s : super string a recortar
******
* Returns:
* void, no retorna nada
*****/

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

    file.close();

    return 0;
}