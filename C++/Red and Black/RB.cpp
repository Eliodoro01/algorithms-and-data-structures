#include <iostream>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key)
        : key(key), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    Node* NIL;

public:
    RedBlackTree() {
        NIL = new Node(0);
        NIL->color = BLACK;
        root = NIL;
    }

   void leftRotate(Node* x) {
        Node* y = x->right;           // y diventa il figlio destro di x (cioè il nodo che salirà al posto di x)

        x->right = y->left;           // il sottoalbero sinistro di y diventa il sottoalbero destro di x
                                    // (cioè il figlio sinistro di y viene "adottato" da x come suo figlio destro)

        if (y->left != NIL) {
            y->left->parent = x;      // se y ha un figlio sinistro (non è NIL), ne aggiorniamo il padre a x
        }

        y->parent = x->parent;        // ora y "sale" al posto di x, quindi il padre di y diventa il padre di x

        if (x->parent == NIL) {
            root = y;                 // se x era la radice, allora y diventa la nuova radice
        } else if (x == x->parent->left) {
            x->parent->left = y;      // se x era figlio sinistro del padre, aggiorniamo quel puntatore a y
        } else {
            x->parent->right = y;     // altrimenti, x era figlio destro, e aggiorniamo quel puntatore a y
        }

        y->left = x;                  // x diventa il figlio sinistro di y
        x->parent = y;                // y diventa il nuovo padre di x
    }

    void rightRotate(Node* y) {
        Node* x = y->left;            // x è il figlio sinistro di y (cioè il nodo che salirà al posto di y)

        y->left = x->right;           // il sottoalbero destro di x diventa il sottoalbero sinistro di y
                                    // (cioè il figlio destro di x viene "adottato" da y come suo figlio sinistro)

        if (x->right != NIL) {
            x->right->parent = y;     // se x ha un figlio destro (non NIL), ne aggiorniamo il padre a y
        }

        x->parent = y->parent;        // ora x "sale" al posto di y, quindi il padre di x diventa il padre di y

        if (y->parent == NIL) {
            root = x;                 // se y era la radice, allora x diventa la nuova radice
        } else if (y == y->parent->right) {
            y->parent->right = x;     // se y era figlio destro del padre, aggiorniamo quel puntatore a x
        } else {
            y->parent->left = x;      // altrimenti, y era figlio sinistro, e aggiorniamo quel puntatore a x
        }

        x->right = y;                 // y diventa il figlio destro di x
        y->parent = x;                // x diventa il nuovo padre di y
    }


    // Metodo per ottenere la radice (per scopi di test)
    Node* getRoot() {
        return root;
    }

    Node* getNIL() {
        return NIL;
    }
};


int main() {
    RedBlackTree tree;

    // Creiamo manualmente 3 nodi
    Node* x = new Node(10);
    Node* y = new Node(20);
    Node* nil = tree.getNIL();  // Puntatore al nodo NIL

    // Impostiamo i collegamenti per simulare un piccolo albero:
    //    x
    //     \
    //      y
    x->right = y;
    y->parent = x;

    x->left = nil;
    y->left = nil;
    y->right = nil;
    x->parent = nil;

    // Impostiamo la radice
    // (notare che tree.root è privato, quindi qui bisognerebbe estendere la classe per settarlo direttamente)
    // Per il test, simuliamo con una funzione interna: usiamo x come radice
    tree.leftRotate(x);  // Eseguiamo la rotazione sinistra su x

    cout << "Dopo leftRotate:\n";
    cout << "Nuova radice: " << y->key << endl;
    cout << "Sinistro di root: " << y->left->key << endl;

    // Ora facciamo una rightRotate su y per tornare alla situazione iniziale
    tree.rightRotate(y);

    cout << "\nDopo rightRotate:\n";
    cout << "Nuova radice: " << x->key << endl;
    cout << "Destro di root: " << x->right->key << endl;

    // Pulizia
    delete x;
    delete y;

    return 0;
}

