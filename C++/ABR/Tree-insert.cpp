#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;

    Node(int key) {
        this->key = key;
        left = right = parent = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        // Trova la posizione per inserire il nuovo nodo
        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        // Imposta il padre del nuovo nodo
        z->parent = y;

        if (y == nullptr) {
            root = z; // L'albero era vuoto, z diventa la radice
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void printInOrder() {
        inorderTraversal(root);
        cout << endl;
    }

    Node* getRoot() {
        return root;
    }
};

int main() {
    BinarySearchTree tree;
    tree.insert(15);
    tree.insert(6);
    tree.insert(18);
    tree.insert(3);
    tree.insert(7);
    tree.insert(17);
    tree.insert(20);

    cout << "In-order traversal dell'ABR: ";
    tree.printInOrder();

    return 0;
}
