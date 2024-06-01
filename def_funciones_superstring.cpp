#include "tda_superstring.cpp"
#include <math.h>

void super_string::juntar(super_string &s){
    if (s.root == nullptr){
        return;
    }
    joinTrees(s.root);
}

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

void super_string::separar(int i, super_string &a, super_string &b){
    if (i <= 0 || i >= length-1){
        a.root = root;
        b.root = nullptr;
        return;
    }

    nodo** arr = new nodo*[length];
    a.root = nullptr;
    b.root = nullptr;
    int j = 0;
    appendArrayInOrder(root, arr, j);
    for (int m = 0; m < length; m++){
        if (m < i){
            a.agregar(arr[m]->c);
        } else {
            b.agregar(arr[m]->c);
        }
    }
}

void super_string::reverso(){
    reverseNodes(root);
}

int super_string::recortar(){
    nodo** arr = new nodo*[length];
    int start = 0;
    int end = length-1;
    int i = 0;
    appendArrayInOrder(root, arr, i);
    balancearABBbasedInArray(arr, start, end);
    height = log2 (length);

    return height;
}

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
    if (nodo == root){
        root = nullptr;
    } else {
        delete nodo;
    }
}

void super_string::appendArrayInOrder(nodo* node, nodo** arr, int& i){
    if (node == nullptr){
        return;
    }

    appendArrayInOrder(node->left, arr, i);
    arr[i++] = node;
    appendArrayInOrder(node->right, arr, i);
}

super_string::nodo* super_string::balancearABBbasedInArray(nodo** arr, int start, int end){
    if (start > end){
        return nullptr;
    }
    int mid = start + (end - start)/2;
    nodo* nodo = arr[mid];
    nodo->left = balancearABBbasedInArray(arr, start, mid-1);
    nodo->right = balancearABBbasedInArray(arr, mid+1, end);
    return nodo;
}

void super_string::joinTrees(nodo* nodo){
    if (nodo == nullptr){
        return;
    }
    this->agregar(nodo->c);
    joinTrees(nodo->left);
    joinTrees(nodo->right);
}

void super_string::reverseNodes(nodo* nodo){
    if (nodo == nullptr){
        return;
    }
    swap(nodo->left, nodo->right);
    reverseNodes(nodo->left);
    reverseNodes(nodo->right);
}