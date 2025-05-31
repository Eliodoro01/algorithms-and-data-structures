#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};

// Classe Node (nodo dell'albero)
class Node
{
private:
    int key;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

public:
    // Costruttore
    Node(int k)
        : key(k), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    // Getter e Setter
    int getKey() const { return key; }
    void setKey(int k) { key = k; }

    Color getColor() const { return color; }
    void setColor(Color c) { color = c; }

    Node *getLeft() const { return left; }
    void setLeft(Node *l) { left = l; }

    Node *getRight() const { return right; }
    void setRight(Node *r) { right = r; }

    Node *getParent() const { return parent; }
    void setParent(Node *p) { parent = p; }

    // La classe RedBlackTree può accedere direttamente ai membri privati
    friend class RedBlackTree;
};

// Classe albero Red-Black
class RedBlackTree
{
private:
    Node *root;
    Node *NIL;

public:
    // Costruttore dell'albero
    RedBlackTree()
    {
        NIL = new Node(0);
        NIL->color = BLACK;
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    // Distruttore (per liberare la memoria)
    ~RedBlackTree()
    {
        deleteTree(root);
        delete NIL;
    }

    // Funzione helper per il distruttore
    void deleteTree(Node* node) {
        if (node != NIL) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }

    // Rotazione a sinistra intorno al nodo x
    void leftRotate(Node *x)
    {
        Node *y = x->right;

        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NIL)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // Rotazione a destra intorno al nodo y
    void rightRotate(Node *y)
    {
        Node *x = y->left;

        y->left = x->right;
        if (x->right != NIL)
        {
            x->right->parent = y;
        }

        x->parent = y->parent;

        if (y->parent == NIL)
        {
            root = x;
        }
        else if (y == y->parent->right)
        {
            y->parent->right = x;
        }
        else
        {
            y->parent->left = x;
        }

        x->right = y;
        y->parent = x;
    }

    // Stampa ricorsiva dell'albero
    void printTree(Node *node, string indent = "", bool last = true)
    {
        if (node != NIL)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "     ";
            }
            else
            {
                cout << "L----";
                indent += "|    ";
            }

            string color = (node->color == RED) ? "RED" : "BLACK";
            cout << node->key << "(" << color << ")" << endl;

            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }

    // Sostituisce il sottoalbero radicato in u con quello radicato in v
    void rbTransplant(Node *u, Node *v)
    {
        if (u->parent == NIL)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    // Trova il nodo con il valore minimo nel sottoalbero
    Node *treeMinimum(Node *x)
    {
        while (x->left != NIL)
        x = x->left;
        return x;
    }

    // Inserimento di un nuovo nodo
    void insert(int key)
    {
        Node *z = new Node(key);
        Node *y = NIL;
        Node *x = root;

        while (x != NIL)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL)
        {
            root = z;
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }

        z->left = NIL;
        z->right = NIL;
        z->color = RED;

        insertFixup(z);
    }

    // Ripristina le proprietà RB dopo l'inserimento
    void insertFixup(Node *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left)
            {
                Node *y = z->parent->parent->right;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                Node *y = z->parent->parent->left;
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    // Funzione per eliminare un nodo
    void rbDelete(int key) {
        Node *z = search(root, key);
        if (z == NIL) {
            cout << "Nodo non trovato nell'albero." << endl;
            return;
        }
        rbDelete(z);
    }

    // Funzione principale per l'eliminazione RB
    void rbDelete(Node *z)
    {
        Node *y = z;                            // y punta al nodo da eliminare o al suo successore
        Node *x;                                // x sarà il nodo che prenderà il posto di y
        Color yOriginalColor = y->color;        // Memorizza il colore originale di y

        if (z->left == NIL)                     // Caso 1: Il nodo ha solo figlio destro
        {
            x = z->right;                       // x prende il figlio destro
            rbTransplant(z, z->right);          // Sostituisce z con il suo figlio destro
        }
        else if (z->right == NIL)               // Caso 2: Il nodo ha solo figlio sinistro
        {
            x = z->left;                        // x prende il figlio sinistro
            rbTransplant(z, z->left);           // Sostituisce z con il suo figlio sinistro
        }
        else                                    // Caso 3: Il nodo ha due figli
        {
            y = treeMinimum(z->right);          // y diventa il successore in-ordine (minimo nel sottoalbero destro)
            yOriginalColor = y->color;          // Memorizza il colore originale del successore
            x = y->right;                       // x prende il figlio destro di y (potrebbe essere NIL)

            if (y->parent == z)                 // Se y è figlio diretto di z
            {
                x->parent = y;                 // Aggiorna il parent di x (anche se x è NIL)
            }
            else                                // Se y non è figlio diretto di z
            {
                rbTransplant(y, y->right);      // Sostituisce y con il suo figlio destro
                y->right = z->right;            // y eredita il sottoalbero destro di z
                y->right->parent = y;           // Aggiorna il parent del sottoalbero destro
            }

            rbTransplant(z, y);                 // Sostituisce z con y
            y->left = z->left;                  // y eredita il sottoalbero sinistro di z
            y->left->parent = y;                // Aggiorna il parent del sottoalbero sinistro
            y->color = z->color;                // y prende il colore originale di z
        }

        delete z;                               // Libera la memoria del nodo eliminato

        if (yOriginalColor == BLACK)            // Se il colore originale del nodo rimosso era nero
        {
            rbDeleteFixup(x);                   // Ripristina le proprietà RB
        }
    }

    // Ripristina le proprietà RB dopo l'eliminazione
    void rbDeleteFixup(Node *x)
    {
        while (x != root && x->color == BLACK)  // Continua finché x non è radice ed è nero
        {
            if (x == x->parent->left)           // Caso: x è figlio sinistro
            {
                Node *w = x->parent->right;     // w è il fratello di x
                if (w->color == RED)            // Caso 1: Fratello rosso
                {
                    w->color = BLACK;           // Fratello diventa nero
                    x->parent->color = RED;      // Parent diventa rosso
                    leftRotate(x->parent);       // Rotazione sinistra sul parent
                    w = x->parent->right;       // Aggiorna w al nuovo fratello
                }

                if (w->left->color == BLACK && w->right->color == BLACK) // Caso 2: Entrambi i figli di w sono neri
                {
                    w->color = RED;              // Fratello diventa rosso
                    x = x->parent;               // Sposta x verso l'alto
                }
                else                            // Almeno un figlio di w è rosso
                {
                    if (w->right->color == BLACK) // Caso 3: Figlio destro di w è nero
                    {
                        w->left->color = BLACK;  // Figlio sinistro di w diventa nero
                        w->color = RED;          // w diventa rosso
                        rightRotate(w);          // Rotazione destra su w
                        w = x->parent->right;    // Aggiorna w al nuovo fratello
                    }
                    // Caso 4: Figlio destro di w è rosso
                    w->color = x->parent->color; // w prende il colore del parent
                    x->parent->color = BLACK;    // Parent diventa nero
                    w->right->color = BLACK;     // Figlio destro di w diventa nero
                    leftRotate(x->parent);       // Rotazione sinistra sul parent
                    x = root;                    // Termina il ciclo
                }
            }
            else                                // Caso simmetrico: x è figlio destro
            {
                Node *w = x->parent->left;      // w è il fratello di x
                if (w->color == RED)            // Caso 1: Fratello rosso
                {
                    w->color = BLACK;           // Fratello diventa nero
                    x->parent->color = RED;      // Parent diventa rosso
                    rightRotate(x->parent);      // Rotazione destra sul parent
                    w = x->parent->left;        // Aggiorna w al nuovo fratello
                }

                if (w->right->color == BLACK && w->left->color == BLACK) // Caso 2: Entrambi i figli di w sono neri
                {
                    w->color = RED;              // Fratello diventa rosso
                    x = x->parent;               // Sposta x verso l'alto
                }
                else                            // Almeno un figlio di w è rosso
                {
                    if (w->left->color == BLACK) // Caso 3: Figlio sinistro di w è nero
                    {
                        w->right->color = BLACK; // Figlio destro di w diventa nero
                        w->color = RED;          // w diventa rosso
                        leftRotate(w);           // Rotazione sinistra su w
                        w = x->parent->left;    // Aggiorna w al nuovo fratello
                    }
                    // Caso 4: Figlio sinistro di w è rosso
                    w->color = x->parent->color; // w prende il colore del parent
                    x->parent->color = BLACK;    // Parent diventa nero
                    w->left->color = BLACK;      // Figlio sinistro di w diventa nero
                    rightRotate(x->parent);      // Rotazione destra sul parent
                    x = root;                   // Termina il ciclo
                }
            }
        }
        x->color = BLACK;                        // Assicura che la radice sia nera
    }

    // Funzione di ricerca
    Node* search(Node* node, int key) {
        if (node == NIL || key == node->key) {
            return node;
        }
        if (key < node->key) {
            return search(node->left, key);
        } else {
            return search(node->right, key);
        }
    }

    // Per test: imposta la radice manualmente
    void setRoot(Node *r)
    {
        root = r;
    }

    // Ottieni la radice (per stampa o test)
    Node *getRoot()
    {
        return root;
    }

    // Ottieni il nodo NIL
    Node *getNIL()
    {
        return NIL;
    }
};

// -------------------- MAIN --------------------

int main()
{
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(17);

    cout << "\nAlbero Red-Black prima della cancellazione:\n";
    tree.printTree(tree.getRoot());

    // Test di cancellazione
    cout << "\nCancellazione del nodo 20...\n";
    tree.rbDelete(20);

    cout << "\nAlbero Red-Black dopo la cancellazione:\n";
    tree.printTree(tree.getRoot());

    return 0;
}