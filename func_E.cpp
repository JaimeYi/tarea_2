#include <iostream>
#include <cmath>
#include <functional>
#include <string>

using namespace std;

class super_string {
    private:
        struct nodo {
            nodo *left = nullptr, *right = nullptr;
            int index;
            char c;
            nodo(int index, char c){
                this->index = index;
                this->c = c;
            }
            nodo(){}
        };
        int height = 0; // Altura del árbol
        int length = 0; // Largo del super-string
        nodo* root = nullptr; // Raíz del super-string
        void printInOrder(nodo* node) {
            if (node == nullptr) return;
            printInOrder(node->left);
            cout << node->c << " ";
            printInOrder(node->right);
        }
        void storeNodesInArray(nodo* node, nodo** arr, int& index);
        nodo* buildBalancedTreeFromArray(nodo** arr, int start, int end);
    public:
        super_string() {}
        void juntar(super_string &s);
        void agregar(char c); // Insertar un caracter en la última posición
        void separar(int i, super_string &a, super_string &b);
        void reverso(); // No debe cambiar la altura del árbol
        int recortar(); // Retorna this->height después de recortar
        string stringizar(); // Debe ser O(n)
        void limpiar(); // Se deben borrar todos los nodos del super-string
        void stringizar_in_order(nodo* nodo, string& str);
        void printInOrder() {
            printInOrder(root);
            cout << endl;
        }
        void limpiarPostOrder(nodo* nodo);
};

void super_string::juntar(super_string &s) {
    if (!s.root) return;

    std::function<void(nodo*)> joinTrees = [&](nodo* node) {
        if (!node) return;
        this->agregar(node->c);
        joinTrees(node->left);
        joinTrees(node->right);
    };

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

void super_string::separar(int i, super_string &a, super_string &b) {
    if (i <= 0 || i >= length) {
        a.root = root;
        b.root = nullptr;
        return;
    }

    a.root = nullptr;
    b.root = nullptr;

    std::function<void(nodo*, super_string&, super_string&)> split = [&](nodo* node, super_string& left, super_string& right) {
        if (!node) return;
        if (node->index < i) {
            left.agregar(node->c);
            split(node->left, left, right);
            split(node->right, left, right);
        } else {
            right.agregar(node->c);
            split(node->left, left, right);
            split(node->right, left, right);
        }
    };

    split(root, a, b);
}

void super_string::reverso() {
    std::function<void(nodo*)> reverseNodes = [&](nodo* node) {
        if (!node) return;
        std::swap(node->left, node->right);
        reverseNodes(node->left);
        reverseNodes(node->right);
    };

    reverseNodes(root);
}

int super_string::recortar() {
    int numNodes = length;
    if (numNodes == 0) return 0;

    nodo** arr = new nodo*[numNodes];
    int index = 0;
    storeNodesInArray(root, arr, index);

    root = buildBalancedTreeFromArray(arr, 0, numNodes - 1);
    height = (int)log2(numNodes);

    delete[] arr;
    return height;
}

void super_string::storeNodesInArray(nodo* node, nodo** arr, int& index) {
    if (node == nullptr) return;
    storeNodesInArray(node->left, arr, index);
    arr[index++] = node;
    storeNodesInArray(node->right, arr, index);
}

super_string::nodo* super_string::buildBalancedTreeFromArray(nodo** arr, int start, int end) {
    if (start > end) return nullptr;
    int mid = start + (end - start) / 2;
    nodo* node = arr[mid];
    node->left = buildBalancedTreeFromArray(arr, start, mid - 1);
    node->right = buildBalancedTreeFromArray(arr, mid + 1, end);
    return node;
}

string super_string::stringizar(){
    string str = "";
    stringizar_in_order(root, str);
    return str;
}

void super_string::limpiar(){
    limpiarPostOrder(root);
    root = nullptr;
    length = 0;
}

void super_string::stringizar_in_order(nodo* nodo, string& str){
    if (nodo == nullptr){
        return;
    }
    stringizar_in_order(nodo->left, str);
    str += nodo->c;
    stringizar_in_order(nodo->right, str);
}

void super_string::limpiarPostOrder(nodo* nodo) {
    if (nodo == nullptr) return;
    limpiarPostOrder(nodo->left);
    limpiarPostOrder(nodo->right);
    delete nodo;
}

int main(){
    int N, M;
    char c;
    super_string s, t;
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> c;
        s.agregar(c);
    }
    cin >> M;
    s.separar(M, t, s);
    s.juntar(t);
    s.reverso();
    cout << s.stringizar() << endl;
    cout << s.recortar() << endl;
    cout << s.stringizar() << endl;
    s.limpiar();
}
