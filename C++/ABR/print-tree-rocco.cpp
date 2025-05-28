#include <iostream>

using namespace std;


class Node{

    private:
        int key;
        Node* parent;
        Node* left;
        Node* right;

        Node(int key){
            this->key = key;
            parent = left = right = nullptr;
        }

    public:
        int get_key(){
            return key;
        }

        Node* get_left(){
            return left;
        }

        Node* get_right(){
            return right;
        }

};

class BinarySearchTreee{

    public:

    void print_tree(Node* node, string prefix = "", bool is_left = true) {
        if (node != nullptr) {
        cout << prefix;

        cout << (is_left ? "├── " : "└── ");
        cout << node->get_key() << endl;

        print_tree(node->get_left(), prefix + (is_left ? "│   " : "    "), true);

        print_tree(node->get_right(), prefix + (is_left ? "│   " : "    "), false);
        }
    }

};