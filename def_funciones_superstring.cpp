#include "tda_superstring.cpp"

void super_string::juntar(super_string &s){}

void super_string::agregar(char c){
    if (root == nullptr){
        root = new nodo(length, c);
    } else {
        nodo* nodo_actual = root;
        while (true){
            if (length < nodo_actual->index){
                if (nodo_actual->left == nullptr){
                    nodo_actual->left = new nodo(length, c);
                    break;
                }
                nodo_actual = nodo_actual->left;
            } else {
                if (nodo_actual->right == nullptr){
                    nodo_actual->right = new nodo(length, c);
                    break;
                }
                nodo_actual = nodo_actual->right;
            }
        }
    }
    length++;
}

void super_string::separar(int i, super_string &s, super_string &b){}

void super_string::reverso(){}

int super_string::recortar(){
    return 0;
}

string super_string::stringizar(){
    string str = "";
    if (root == nullptr){
        return str;
    } else {
        for (int i = 0; i < length; i++){
            nodo* nodo_actual = root;
            //tengo que visitar todos los nodos hasta encontrar el que tenga 
            //el indice "i" y se deben ir concatenando
        }
    }
    return "hola";
}

void super_string::limpiar(){}