#include <functional>
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
    /*
    int index_nueva_raiz = length/2;

    if (length == 2){
        cout << root->c;
        return 1;
    } else if (length == 3){
        root->right->left = root;
        nodo* aux = root->right;
        root->right = nullptr;
        root = aux;
        cout << root->c;
        return 1;

    } else if (length%2 == 0 && length != 2){
        
    } else if (length%2 != 0 && length != 3){

    }

    return 0;
    */
}

string super_string::stringizar(){
    string str = "";
    stringizar_in_order(root, str);
    return str;
}

void super_string::limpiar(){}

void super_string::stringizar_in_order(nodo* nodo, string& str){
    if (nodo == nullptr){
        return;
    }
    stringizar_in_order(nodo->left, str);
    str += nodo->c;
    stringizar_in_order(nodo->right, str);
}