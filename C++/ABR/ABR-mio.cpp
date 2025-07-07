#include <stdio.h>
#include <iostream>
#include <fstream>


using namespace std;

class Node{

    private:
        Node* left;
        Node* right;
        Node* parent;
        int value;

    public:
        Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr){}

        Node* getLeft(){return left;}
        Node* getRight(){return right;}
        Node* getParent(){return parent;}
        int getValue(){return value;}

        void setLeft(Node* node){left = node;}
        void setRigh(Node* node){right = node;}
        void setParent(Node* node){parent = node;}
};

class ABR{

    private:
        Node* root;


        Node* maximum(Node* x){
            if(x == nullptr)
                return nullptr;
            while(x->getRight() != nullptr){
                x = x->getRight();
            }

            return x;
        }

        Node* minimum(Node* x){
            if(x == nullptr)
                return nullptr;
            while(x->getLeft() != nullptr){
                x = x->getLeft();
            }

            return x;
        }

        Node* insertRec(Node* node, int key){
            if(node == nullptr){
                return new Node(key);
            }

            if(key < node->getValue()){
                Node* leftChild = insertRec(node->getLeft(), key);
                leftChild->setParent(node);
                node->setLeft(leftChild);
            }
            else{
                Node* rightChild = insertRec(node->getRight(), key);
                node->setRigh(rightChild);
                rightChild->setParent(node);
            }

            return node;
        }

        void printPre(Node* root, ofstream& out){

            if(root == nullptr)
                return;

            out<< "Key: "<<root->getValue() << endl;
            printPre(root->getLeft(), out);
            printPre(root->getRight(), out);
        }

        void printPost(Node* root, ofstream& out){
            if(root == nullptr)
                return;
            
            printPost(root->getLeft(), out);
            printPost(root->getRight(),out);
            out << "key: "<< root->getValue()<<endl;
        }

        void printIn(Node* root, ofstream& out){
            if(root == nullptr)
                return;
            
            printIn(root->getLeft(), out);
            out << " key: "<< root->getValue()<<endl;
            printIn(root->getRight(), out);
        }

        Node* searchN(Node* x, int key){
            if(x == nullptr || key == x->getValue()){
                return x;
            }

            if(key < x->getValue()){
                return searchN(x->getLeft(), key);
            }
            else
                return searchN(x->getRight(), key);

        }


    public:
        ABR() : root(nullptr){}

        void insert( int key){ root = insertRec(root, key);}
        void printInOrder(ofstream& out){ printIn(root, out);}
        void printPreOrder(ofstream& out){ printPre(root, out);}
        void printPostOrder(ofstream& out){ printPost(root,out);}
        Node* search(int key){ return searchN(root, key);}
        
        Node* getPredecessor(Node* x){
            if(x == nullptr)
                return nullptr;

            if(x->getLeft() != nullptr)
                return maximum(x->getLeft());

            Node* y = x->getParent();

            while(y != nullptr && x == y->getLeft()){
                x = y;
                y = y->getParent();
            }
            return y;
        }

        Node* getSuccessor(Node* x){
            if(x == nullptr)
                return nullptr;

            if(x->getRight() != nullptr)
                return minimum(x->getRight());

            Node* y = x->getParent();

            while(y != nullptr && x == y->getRight()){
                x = y;
                y = y->getParent();
            }
            return y;
        }

                

};


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr;
    int k;

    while (in >> k)
        abr.insert(k);

    abr.printPreOrder(out);

    // esempio: voglio il predecessore di 14
    int target = 14;
    Node* node = abr.search(target);

    if (node != nullptr) {
        Node* pred = abr.getPredecessor(node);
        if (pred != nullptr)
            cout << "Il predecessore di " << node->getValue() << " è: " << pred->getValue() << endl;
        else
            cout << "Il nodo " << node->getValue() << " non ha predecessore." << endl;
    } else {
        cout << "Nodo " << target << " non trovato nell'albero." << endl;
    }

    return 0;
}
