#include <iostream>                                // Libreria per input/output
using namespace std;

class Node {
public:
    int key;                                       // Valore del nodo
    Node* left;                                    // Puntatore al figlio sinistro
    Node* right;                                   // Puntatore al figlio destro
    Node* parent;                                  // Puntatore al padre

    Node(int key) {
        this->key = key;                           // Inizializza il valore del nodo
        left = right = parent = nullptr;           // Inizializza i puntatori a null
    }
};

class BinarySearchTree {
private:
    Node* root;                                    // Radice dell’albero

    void transplant(Node* u, Node* v) {            // Sostituisce il sottoalbero radicato in u con v
        if (u->parent == nullptr) {
            root = v;                              // Se u è la radice, aggiorna la radice
        } else if (u == u->parent->left) {
            u->parent->left = v;                   // Se u è figlio sinistro, aggiorna il padre
        } else {
            u->parent->right = v;                  // Se u è figlio destro, aggiorna il padre
        }
        if (v != nullptr) {
            v->parent = u->parent;                 // Imposta il nuovo padre per v
        }
    }

    Node* treeMinimum(Node* node) {                // Trova il minimo del sottoalbero
        while (node->left != nullptr) {
            node = node->left;                     // Vai sempre a sinistra
        }
        return node;                               // Restituisce il nodo minimo
    }

    Node* treeMaximum(Node* node) {                // Trova il massimo del sottoalbero
        while (node->right != nullptr) {
            node = node->right;                    // Vai sempre a destra
        }
        return node;                               // Restituisce il nodo massimo
    }

    Node* successor(Node* x) {                     // Trova il successore in ordine
        if (x->right != nullptr)
            return treeMinimum(x->right);          // Il minimo del sottoalbero destro

        Node* y = x->parent;
        while (y != nullptr && x == y->right) {
            x = y;
            y = y->parent;                         // Risali l’albero finché non cambi direzione
        }
        return y;
    }

    Node* predecessor(Node* x) {                   // Trova il predecessore in ordine
        if (x->left != nullptr)
            return treeMaximum(x->left);           // Il massimo del sottoalbero sinistro

        Node* y = x->parent;
        while (y != nullptr && x == y->left) {
            x = y;
            y = y->parent;                         // Risali finché non cambi direzione
        }
        return y;
    }

public:
    BinarySearchTree() {
        root = nullptr;                            // Inizializza la radice a null
    }

    void insert(int key) {
        Node* z = new Node(key);                   // Crea nuovo nodo
        Node* y = nullptr;                         // Nodo padre
        Node* x = root;                            // Nodo corrente

        while (x != nullptr) {                     // Cerca la posizione per il nuovo nodo
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;                             // Imposta il padre di z
        if (y == nullptr) {
            root = z;                              // Se l’albero era vuoto, z è la radice
        } else if (z->key < y->key) {
            y->left = z;                           // Inserisce a sinistra
        } else {
            y->right = z;                          // Inserisce a destra
        }
    }

    void deleteNode(Node* z) {
        if (z->left == nullptr) {
            transplant(z, z->right);               // Caso 1: solo figlio destro
        } else if (z->right == nullptr) {
            transplant(z, z->left);                // Caso 2: solo figlio sinistro
        } else {
            Node* y = treeMinimum(z->right);       // Trova il successore
            if (y->parent != z) {
                transplant(y, y->right);           // Rimpiazza y con suo figlio destro
                y->right = z->right;               // Collega il sottoalbero destro
                if (y->right != nullptr)
                    y->right->parent = y;
            }
            transplant(z, y);                      // Sostituisci z con y
            y->left = z->left;                     // Collega il sottoalbero sinistro
            if (y->left != nullptr)
                y->left->parent = y;
        }
        delete z;                                  // Dealloca il nodo
    }

    Node* search(int key) {
        Node* current = root;
        while (current != nullptr && current->key != key) {
            if (key < current->key)
                current = current->left;           // Vai a sinistra se il valore è minore
            else
                current = current->right;          // Vai a destra altrimenti
        }
        return current;                            // Ritorna il nodo trovato o nullptr
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);          // Visita sinistra
            cout << node->key << " ";              // Stampa il nodo
            inorderTraversal(node->right);         // Visita destra
        }
    }

    void printInOrder() {
        inorderTraversal(root);                    // Avvia la visita dall’alto
        cout << endl;
    }

    Node* getRoot() {
        return root;                               // Restituisce la radice dell’albero
    }
};

int main() {
    BinarySearchTree tree;                         // Crea l'albero

    tree.insert(15);                               // Inserisce 15
    tree.insert(6);                                // Inserisce 6
    tree.insert(18);                               // Inserisce 18
    tree.insert(3);                                // Inserisce 3
    tree.insert(7);                                // Inserisce 7
    tree.insert(17);                               // Inserisce 17
    tree.insert(20);                               // Inserisce 20

    cout << "In-order prima della cancellazione: ";
    tree.printInOrder();                           // Stampa ordinata prima della cancellazione

    Node* z = tree.search(6);                      // Cerca il nodo con chiave 6
    if (z != nullptr) {
        tree.deleteNode(z);                        // Cancella il nodo
    }

    cout << "In-order dopo la cancellazione di 6: ";
    tree.printInOrder();                           // Stampa dopo la cancellazione

    return 0;
}
