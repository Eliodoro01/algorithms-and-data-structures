#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;


class Node{

    private:
        Node* predecessor;
        Node* left;
        Node* right;
        int value;

    public:

        Node(int v) : value(v), left(nullptr), right(nullptr), predecessor(nullptr){}

        Node* getPredecessor(){return predecessor;}
        Node* getLeft(){return left;}
        Node* getRight(){return right;}
        int getValue(){return value;}

        void setPredecessor(Node* p){predecessor = p;}
        void setLeft(Node* l){left = l;}
        void setRight(Node* r){right = r;}
};

class ABR{

    private:
        Node* root;

        Node* insertRec(Node* node, int key){
            if(node == nullptr)
                return new Node(key);
            
            if(key < node->getValue()){
                Node* leftChild = insertRec(node->getLeft(),key);
                node->setLeft(leftChild);
                leftChild->setPredecessor(node);
            }
            else{
                Node* rightChild = insertRec(node->getRight(), key);
                rightChild->setPredecessor(node);
                node->setRight(rightChild);
            }

            return node;
        }

        Node* minimum(Node* x){

            while(x->getLeft() != nullptr){
                x = x->getLeft();
            }
            return x;
        }

        Node* maximum(Node* x){

            while(x->getRight() != nullptr){
                x = x->getRight();
            }
            return x;
        }

    public:
        ABR() : root(nullptr){};

        Node* getSuccessor(Node* x){
            if(x == nullptr)
                return nullptr;
            
            if(x->getRight() != nullptr){
                return minimum(x->getRight());
            }

            Node* y = x->getPredecessor();

            while(y != nullptr && x == y->getRight()){
                x= y;
                y = y->getPredecessor();
            }

            return y;
        }

        Node* getPredecessor(Node* x){

            if(x == nullptr){
                return nullptr;
            }

            if(x->getLeft() != nullptr){
                return maximum(x->getLeft());
            }

            Node* y = x->getPredecessor();
            while(y != nullptr && x == y->getLeft()){
                x = y;
                y = y->getPredecessor();
            }

            return y;

        }

        Node* search(Node* node, int key){

            if(node == nullptr || node->getValue() == key)
                return node;
            
            if(key < node->getValue()){
                return search(node->getLeft(), key);
            }
            else
                return search(node->getRight(), key);
            
        }

        void preorder(Node* node,ofstream& out){

            if(node == nullptr)
                return;

            out << "value: " << node->getValue() << 
        }


};