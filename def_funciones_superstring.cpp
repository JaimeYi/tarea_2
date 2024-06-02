#include "tda_superstring.cpp"


/*****
* void juntar
******
* Esta función une un ABB dado, al ABB desde el que se solicita la función la función
******
* Input:
* super_string &s : ABB que sera unido al ABB desde el que se callea la función
******
* Returns:
* void, no retorna nada
*****/

void super_string::juntar(super_string &s){
    if (s.root == nullptr){
        return;
    }
    s.aumentarIndices(s.root, length);
    joinTrees(s.root);
}

/*****
* void aumentarIndices
******
* esta función se utiliza en el metodo 'juntar', aumenta el indice de cada nodo del ABB a juntar, para
* que asi se agregue de forma correcta el segundo ABB al primero
******
* Input:
* nodo* nodo : nodo al que se le aumentara el indice
* int largo : largo del primer ABB para que los indices del segundo ABB comiencen justo al final de los 
*             del primer ABB
* Returns:
* void, no retorna nada
*****/

void super_string::aumentarIndices(nodo* nodo, int largo){
    if (nodo == nullptr){
        return;
    }
    aumentarIndices(nodo->left, largo);
    nodo->index += largo;
    aumentarIndices(nodo->right, largo);
}

/*****
* void joinTrees
******
* se recorre el ABB(2) que se quiere unir al ABB(1) original en in-order y se 
* agrega cada caracter del ABB(2) al ABB(1)
******
* Input:
* nodo* nodo : nodo del que se sacara el caracter para agregarlo al ABB(1)
******
* Returns:
* void, no retorna nada
*****/

void super_string::joinTrees(nodo* nodo){
    if (nodo == nullptr){
        return;
    }
    joinTrees(nodo->left);
    this->agregar(nodo->c);
    joinTrees(nodo->right);
}

/*****
* void agregar
******
* esta función agregara siempre los nodos al final del ABB, por esa 
* condicion es que en la funcion solo se recorre el ABB a traves de los hijos a la derecha de cada nodo
******
* Input:
* char c : caracter que se agregara al ABB en forma de nodo
******
* Returns:
* void, no retorna nada
*****/

void super_string::agregar(char c){
    if (root == nullptr){
        root = new nodo(length, c);
    } else {
        nodo* nodo_actual = root;
        while (true){
            if (nodo_actual->right == nullptr){
                nodo_actual->right = new nodo(length, c);
                break;
            }
            nodo_actual = nodo_actual->right;
        }
    }
    length++;
}

/*****
* void separar
******
* esta función pide dos super_strings y un indice donde el superstring se partira en 2, en el primer super_string se guarda
* desde la mitad del super_string desde el que se solicita la función hasta el inicio de este mismo, y en el segundo super_string
* se guarda desde la mitad del super_string desde el que se solicita la función hasta el final del mismo.
******
* Input:
* int i : representa la posición donde se realizara la división del ABB
* super_string& a : en este parametro se almacenara la parte izquierda de la división
* super_string& b : en este parametro se almacenara la parte derecha de la división
******
* Returns:
* void, no retorna nada
*****/

void super_string::separar(int i, super_string &a, super_string &b){
    if (i <= 0){
        a.root = nullptr;
        b.root = root;
        return;
    } else if (i >= length){
        a.root = root;
        b.root = nullptr;
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

/*****
* void appendArrayInOrder
******
* en esta función se recorre el ABB in-order y cada nodo del ABB se agrega a un array dado en la función recortar
******
* Input:
* nodo* node: nodo que se guardara en el array
* nodo** arr: array donde se agregan los nodos encontrados
* int& i: contador partido en 0 que servira para ir avanzando posiciones en el array al momento de asignar los nodos en este
* Returns:
* void, no retorna nada
*****/

void super_string::appendArrayInOrder(nodo* node, nodo** arr, int& i){
    if (node == nullptr){
        return;
    }

    appendArrayInOrder(node->left, arr, i);
    arr[i++] = node;
    appendArrayInOrder(node->right, arr, i);
}

/*****
* void reverso
******
* la función reverso invierte el orden de todos los nodos del ABB desde el que se solicitó
******
* Input:
* no recibe parametros de entrada
******
* Returns:
* void, no retorna nada
*****/

void super_string::reverso(){
    reverseNodes(root);
}

/*****
* void reverseNodes
******
* función base de la función 'reversa', en cada iteracion de la recursividad de la función se intercambia el nodo
* derecho de un nodo dado con el nodo izquierdo del mismo
******
* Input:
* nodo* nodo : nodo donde se realizara las operaciones de la función
******
* Returns:
* void, no retorna nada
*****/

void super_string::reverseNodes(nodo* nodo){
    if (nodo == nullptr){
        return;
    }
    swap(nodo->left, nodo->right);
    reverseNodes(nodo->left);
    reverseNodes(nodo->right);
}

/*****
* int recortar
******
* la función recortar realiza un balanceo del super_string desde el ABB que se solicita para que asi el costo operacional al recorrer 
* el camino más largo pase de O(n) a O(log n)
******
* Input:
* no recibe parametros de entrada
******
* Returns:
* int, el retorno entrega la altura del arbol despues de haberse realizado la operacion de recorte
*****/

int super_string::recortar(){
    nodo** arr = new nodo*[length];
    int start = 0;
    int end = length-1;
    int i = 0, h1 = 0, h2 = 0;
    appendArrayInOrder(root, arr, i);
    root = balancearABBbasedInArray(arr, start, end);
    calcularAlturaLeft(root, h1);
    calcularAlturaRight(root, h2);
    h1>h2?height=h1:height=h2;

    return height;
}

/*****
* nodo* balancearABBbasedInArray
******
* la función busca el nodo que se encuentre a la mitad, habiendo ordenando los nodos de menor a mayor anteriormente, estableciendo
* el nodo central como padre de los siguientes 2 nodos que se encuentren en la mitad de cada 'sub array' que queda si el array
* lo separamos en la mitad y asi recursivamente hasta terminar de armar denuevo el ABB
******
* Input:
* nodo** arr : array donde se ira buscando el valor medio
* int start : valor donde inicia el array (en el sub array derecho se usara el valor medio obtenido + 1 como valor donde inicia el array)
* int end: valor donde inicia el array (en el sub array izquierdo se usara el valor medio obtenido -1 como valor donde termina el array)
* Returns:
* nodo*, se retorna el nodo que sera la nueva raiz del ABB
*****/

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

/*****
* void calcularAlturaLeft
******
* por la forma en la que se creara el ABB el nodo con mayor altura siempre estara lo más a la izquierda o
* derecha posible dentro del arbol, por lo que en este caso se recorre cada nodo izquierdo posible, y por 
* cada iteracion de la función se sumara 1 al contador
******
* Input:
* nodo* nodo : nodo donde se buscara el nodo izquierdo
* int& v : contador donde se guardara la altura final obtenida en la función
******
* Returns:
* void, no retorna nada
*****/

void super_string::calcularAlturaLeft(nodo* nodo, int& v){
    if (nodo == nullptr){
        return;
    }

    v+=1;
    calcularAlturaLeft(nodo->left, v);
}

/*****
* void calcularAlturaRight
******
* por la forma en la que se creara el ABB el nodo con mayor altura siempre estara lo más a la izquierda o
* derecha posible dentro del arbol, por lo que en este caso se recorre cada nodo derecho posible, y por
* cada iteracion de la función se sumara 1 al contador
******
* Input:
* nodo* nodo : nodo donde se buscara el nodo derecho
* int& v : contador donde se guardara la altura final obtenida en la función
******
* Returns:
* void, no retorna nada
*****/

void super_string::calcularAlturaRight(nodo* nodo, int& v){
    if (nodo == nullptr){
        return;
    }

    v+=1;
    calcularAlturaRight(nodo->right, v);
}

/*****
* string stringizar
******
* esta función recorre el ABB y va agregando el caracter de cada nodo a un string vacio para obtener el string contenido en el ABB
******
* Input:
* no recibe parametros de entrada
******
* Returns:
* string, sera el string que estaba contenido en el ABB
*****/

string super_string::stringizar(){
    string str = "";
    stringizar_in_order(root, str);
    return str;
}

/*****
* void stringizar_in_order
******
* esta funcion es la base de la función 'stringizar', se recorre el ABB in-order de forma recursiva y
* se va sumando cada caracter encontrado al string vacio dado en la función stringizar
******
* Input:
* nodo* nodo : el caracter incluido en este nodo sera agregado al string dado 
* string& str: es el string dado en la función 'stringizar'
******
* Returns:
* void, no retorna nada
*****/

void super_string::stringizar_in_order(nodo* nodo, string& str){
    if (nodo == nullptr){
        return;
    }
    stringizar_in_order(nodo->left, str);
    str += nodo->c;
    stringizar_in_order(nodo->right, str);
}

/*****
* void limpiar
******
* esta función deja al ABB sin nodos
******
* Input:
* no recibe parametros de entrada
******
* Returns:
* void, no retorna nada
*****/

void super_string::limpiar(){
    limpiarPostOrder(root);
}

/*****
* void limpiarPostOrder
******
* la función 'limpiar' se basa en esta función, en esta función se recorre el ABB en post-order para asi evitar 
* eliminar la raiz del ABB antes de eliminar el resto de nodos, se elimina cada nodo al que se llega
******
* Input:
* nodo* nodo : nodo que sera eliminado
******
* Returns:
* void, no retorna nada
*****/

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