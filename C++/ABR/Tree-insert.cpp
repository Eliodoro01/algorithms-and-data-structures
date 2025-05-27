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

    // Sostituisce il sottoalbero radicato in u con quello radicato in v
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

    // Restituisce il minimo del sottoalbero radicato in node
    Node* treeMinimum(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int key) {
        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }

    void deleteNode(Node* z) {
        if (z->left == nullptr) {
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            transplant(z, z->left);
        } else {
            Node* y = treeMinimum(z->right);
            if (y->parent != z) {
                transplant(y, y->right);
                y->right = z->right;
                if (y->right != nullptr)
                    y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            if (y->left != nullptr)
                y->left->parent = y;
        }
        delete z;
    }

    Node* search(int key) {
        Node* current = root;
        while (current != nullptr && current->key != key) {
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return current;
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

    cout << "In-order prima della cancellazione: ";
    tree.printInOrder();

    Node* z = tree.search(6);
    if (z != nullptr) {
        tree.deleteNode(z);
    }

    cout << "In-order dopo la cancellazione di 6: ";
    tree.printInOrder();

    return 0;
}
