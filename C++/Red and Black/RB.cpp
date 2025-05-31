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
        NIL->left = NIL->right = NIL->parent = nullptr;
        root = NIL;
    }

    // Distruttore (per liberare il nodo NIL)
    ~RedBlackTree()
    {
        delete NIL;
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

    // Sostituisce il sottoalbero radicato in u con quello radicato in v nel Red-Black Tree
    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (v != nullptr) {
            v->parent = u->parent;
        }
    }


    void insert(int key){

        Node *z = new Node(key);
        Node *y = NIL;
        Node *x = root;

        while (x != NIL){
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == NIL){
            root = z;
        }
        else if (z->key < y->key){
            y->left = z;
        }
        else{
            y->right = z;
        }

        z->left = NIL;
        z->right = NIL;
        z->color = RED;

        insertFixup(z);
    }

    void insertFixup(Node *x){

        while (x->parent->color == RED) {

            if (x->parent == x->parent->parent->left){

                Node *uncle = x->parent->parent->right; 
                if (uncle->color == RED){

                    // Caso 1
                    x->parent->color = BLACK;
                    uncle->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else{

                    if (x == x->parent->right)
                    {
                        // Caso 2
                        x = x->parent;
                        leftRotate(x);
                    }
                    // Caso 3
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    rightRotate(x->parent->parent);
                }
            }
            else{
                // Simmetrico
                Node *y = x->parent->parent->left;
                if (y->color == RED){

                    x->parent->color = BLACK;
                    y->color = BLACK;
                    x->parent->parent->color = RED;
                    x = x->parent->parent;
                }
                else{

                    if (x == x->parent->left){
                        
                        x = x->parent;
                        rightRotate(x);
                    }
                    x->parent->color = BLACK;
                    x->parent->parent->color = RED;
                    leftRotate(x->parent->parent);
                }
            }
        }
        root->color = BLACK;
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

    cout << "\nAlbero Red-Black prima di inserire un altro nodo:\n";
    tree.printTree(tree.getRoot());

    tree.insert(17);

    cout << "\nAlbero Red-Black DOPO aver inserito un altro nodo:\n";
    tree.printTree(tree.getRoot());

    return 0;
}