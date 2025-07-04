#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

class Node{

    private:
        Node* parent;
        Node* left;
        Node* right;
        int value;

    public:
        Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr){}

        Node* getLeft(){return left;}
        Node* getRight(){return right;}
        Node* getParent(){return parent;}
        int getValue(){return value;}

        void setLeft(Node* l){left = l;}
        void setRight(Node* r){right = r;}
        void setParent(Node* p){parent = p;}

};

class ABR{

    private:
        Node* root;

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
                rightChild->setParent(node);
                node->setRight(rightChild);
            }

            return node;
        }

        Node* maximum(Node* node){
            if(node == nullptr){
                return nullptr;
            }

            while(node->getRight() != nullptr){
                node = node->getRight();
            }
            return node;
        }

        Node* minimum(Node* node){
            if(node == nullptr){
                return nullptr;
            }

            while(node->getLeft() != nullptr){
                node = node->getLeft();
            }
            return node;
        }

        Node* searchN(Node* node, int key){
            
            if(node == nullptr || node->getValue() == key){
                return node;
            }


            if(key > node->getValue()){
                return searchN(node->getRight(), key);
            }
            else{
                return searchN(node->getLeft(), key);
            }
        }

        void printInOrder(ofstream& out, Node* root){

            if(root == nullptr){
                return;
            }

            printInOrder(out, root->getLeft());
            out <<"Node: "<< root->getValue() << " ";
            printInOrder(out, root->getRight());
        }

        void printPreOrder(ofstream& out, Node* root){
            if(root == nullptr){
                return;
            }

            out<<"Node: "<<root->getValue() << " ";
            printPreOrder(out, root->getLeft());
            printPreOrder(out, root->getRight());
        }

        void printPostOrder(ofstream& out, Node* root){
            if(root == nullptr){
                return;
            }
  
            printPostOrder(out, root->getLeft());
            printPostOrder(out, root->getRight());
            out<<"Node: "<<root->getValue() << " ";
        }




    public:
        ABR(ifstream& in) : root(nullptr){ load(in);}

        void insert(int key){ root = insertRec(root, key);}
        Node* search(int key){ return searchN(root, key);}
        void printPre(ofstream& out){ printPreOrder(out, root);}
        void printPost(ofstream& out){ printPostOrder(out, root);}
        void printIn(ofstream& out){printInOrder(out, root);}


        Node* predecessor(int key){

            Node* x = search(key);

            if(x == nullptr){
                return nullptr;
            }

            if(x->getLeft() != nullptr){
                return maximum(x->getLeft());
            }

            Node* y;
            y = x->getParent();

            while(y != nullptr && x == y->getLeft()){
                x = y;
                y = y->getParent();
            }

             cout << "predecessor: " << y->getValue()<<endl;
            return y;

        }


        Node* successor(int key){

            Node* x = search(key);

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

            cout << "successor: " << y->getValue()<<endl;

            return y;
        }

        void load(ifstream& in){
            string totalToken;
            while(getline(in, totalToken)){
                if(totalToken.front() == '<')
                    totalToken = totalToken.substr(1);
                if(totalToken.back() == '>')
                    totalToken.pop_back();

                for(char& c : totalToken){
                    if(c == ','){
                        c = ' ';
                    }
                }

                int k;
                istringstream stream(totalToken);

                while(stream >> k){
                    insert(k);
                }
            }
        }      

};

int main(){
    ifstream in("input.txt");
    ofstream out("output.txt");

    ABR abr(in);
    Node* node;

    node = abr.predecessor(12);
    if(node)
        cout << "predecessor: " << node->getValue() << endl;
    else
        cout << "predecessor: NONE" << endl;
    abr.printPre(out);
    out << endl;
    abr.printIn(out);
    out << endl;
    abr.printPost(out);
    out << endl;
   

    in.close();
    out.close();
}
