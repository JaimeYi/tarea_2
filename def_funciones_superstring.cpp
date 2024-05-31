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

int super_string::recortar(){}

string super_string::stringizar(){
    string str = "";
    stringizar_in_order(root, str);
    return str;
}

void super_string::limpiar(){
    limpiarPostOrder(root);
}

void super_string::stringizar_in_order(nodo* nodo, string& str){
    if (nodo == nullptr){
        return;
    }
    stringizar_in_order(nodo->left, str);
    str += nodo->c;
    stringizar_in_order(nodo->right, str);
}

void super_string::limpiarPostOrder(nodo* nodo){
    if (nodo == nullptr){
        return;
    }

    limpiarPostOrder(nodo->left);
    limpiarPostOrder(nodo->right);
    delete nodo;
}