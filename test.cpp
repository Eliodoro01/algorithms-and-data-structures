#include <iostream>

using namespace std;


class Node{

    public:
    int key;

    Node* right;
    Node* left;
    Node* parent;

    Node(int key){
        this->key = key;
        left = right = parent = nullptr;
    }
};


class BinarySearchTree{

    private:

    Node* root;

    void transplant(Node* u, Node* v){

        if(u->parent == nullptr){
            root = v;
        }
        else if(u == u->parent->left){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }

        if(v != nullptr){
            v->parent = u->parent;
        }
    }

    Node* treeMinimum(Node* node){

        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    public:

    BinarySearchTree(){
        root = nullptr;
    }

    void insert(int key){

        Node* z = new Node(key);
        Node* y = nullptr;
        Node* x = root;

        while(x != nullptr){
            y = x;
            if(z->key < x->key){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }

        z->parent = y;

        if(y == nullptr){
            root = z;
        }
        else if(z->key < y->key){
            y->left = z;
        }
        else{
            y->right = z;
        }
    }

    

};