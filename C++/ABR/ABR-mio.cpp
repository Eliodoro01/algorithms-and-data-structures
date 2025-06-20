#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Node{

    private:
        int key;
        char character;
        Node* parent;
        Node* left;
        Node* right;

    public:
        Node(int k, char c) : key(k), character(c), parent(nullptr), left(nullptr), right(nullptr){}

        int getKey(){return key;}
        char getChar(){return character;}
        Node* getParent(){return parent;}
        Node* getLeft(){return left;}
        Node* getRight(){return right;}

        void setParent(Node* p){parent = p;}
        void setLeft(Node* l){left = l;}
        void setRight(Node* r){right = r;}
};


class ABR{

    private:
        Node* root;

        Node* insertRec(Node* node, int key, char character){
            if(node == nullptr)
                return new Node(key, character);

            if(key < node->getKey()){
                Node* leftChild = insertRec(node->getLeft(), key, character);
                node->setLeft(leftChild);
                leftChild->setParent(node);
            }
            else{
                Node* rightChild = insertRec(node->getRight(), key, character);
                node->setRight(rightChild);
                rightChild->setParent(node);
            }

            return node;

        }

        void preorderRec(Node* node, ofstream& out){
            if(node == nullptr){
                return;
            }

            out<<"key: "<< node->getKey()<< ", character: "<<node->getChar()<<endl;
            preorderRec(node->getLeft(), out);
            preorderRec(node->getRight(), out);
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
        ABR(): root(nullptr){}

        Node* getRoot(){return root;}

        void insert(int key, char character){ root = insertRec(root, key, character);}
        void preorder(ofstream& out){preorderRec(root, out);}

        Node* search(Node* node, int key){
            if(node == nullptr || node->getKey()== key){
                return node;
            }
            if(key < node->getKey()){
                return search(node->getLeft(), key);
            }
            else{
                return search(node->getRight(), key);
            }
        }


        Node* getSuccessor(Node* x){
            if(x == nullptr){
                return nullptr;
            }

            if(x->getRight() != nullptr){
                return minimum(x->getRight());
            }

            Node* y = x->getParent();

            while(y != nullptr && x == y->getRight()){
                x = y;
                y = y->getParent();
            }

            return y;
        }

        void writeSuccessor(Node* x, ofstream& out){

            Node* succ = getSuccessor(x);

            if(succ != nullptr){
                out << "Successor's key: "<< succ->getKey() << ", successor's character: " << succ->getChar()<<endl;
            }
            else
                out << "This node doesn't have a successor!"<<endl;
        }

        Node* getPredecessor(Node* x){
            if(x == nullptr){
                return nullptr;
            }

            if(x->getLeft() != nullptr){
                return maximum(x->getLeft());
            }

            Node* y = x->getParent();
            while(y != nullptr && x == y->getLeft()){
                x = y;
                y = y->getParent();
            }

            return y;
        }

        void writePredecessor(Node* x, ofstream& out) {
            Node* pred = getPredecessor(x);

            if (pred != nullptr)
                out << "Predecessor's key: " << pred->getKey() << ", predecessor's character: " << pred->getChar() << endl;
            else
                out << "This node doesn't have a predecessor!" << endl;
        }
        
        void transplant(Node* x, Node* y) {

            if (x->getParent() == nullptr)
                root = y;
            else if (x == x->getParent()->getLeft())
                x->getParent()->setLeft(y);
            else
                x->getParent()->setRight(y);

            if (y != nullptr)
                y->setParent(x->getParent());
        }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr;

    int k;
    char c;
    while (in >> k >> c)
        abr.insert(k, c);

    abr.preorder(out);

    Node* x = abr.search(abr.getRoot(), 15);
    abr.writeSuccessor(x, out);

    x = abr.search(abr.getRoot(), 15);
    abr.writePredecessor(x, out);

    in.close();
    out.close();

    /*
    abr.generateHuffmanTable();

    string encodedString = abr.encodeString("ACE");
    cout << "Encoded string: " << encodedString << endl;

    string decodedString = abr.decodeString(encodedString);
    cout << "Decoded string: " << decodedString << endl;


    x = abr.search(abr.getRoot(), 30);
    Node* y = abr.search(abr.getRoot(), 50);
    abr.transplant(x,y);
    abr.preorder(out);
    out.close();
    */

    return 0;
}
