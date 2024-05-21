#include <string>
#include <iostream>

using namespace std;

class super_string {
    private:
        struct nodo {
            nodo *left = nullptr, *right = nullptr;
            int index;
            char c;
            nodo(int index, char c):index(index), c(c) {}
            nodo(){}
        };
        int height = 0; // Altura del árbol
        int length = 0; // Largo del super-string
        nodo* root = nullptr; // Raíz del super-string
        void imprimirInOrden(nodo* root) {
            if (root == nullptr) {
                return;
            }
            imprimirInOrden(root->left);  // Visitar subárbol izquierdo
            cout << root->c;       // Imprimir el nodo actual
            imprimirInOrden(root->right); // Visitar subárbol derecho
        }
    public:
        super_string() {}
        void juntar(super_string &s);
        void agregar(char c); // Insertar un caracter en la última posición
        // En la izquierda esta el super_string a y en la derecha el super_string b
        void separar(int i, super_string &a, super_string &b);
        void reverso(); // No debe cambiar la altura del árbol
        int recortar(); // Retorna this->height después de recortar
        string stringizar(); // Debe ser O(n)
        void limpiar(); // Se deben borrar todos los nodos del super-string
        void imprimir() {
            imprimirInOrden(root);
            cout << endl;
        }
};
