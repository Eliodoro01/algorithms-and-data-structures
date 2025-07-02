#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <climits>

using namespace std;

enum VisitType { inorder, preorder, postorder };

template <typename T>
class Node {
private:
    T key;
    char character;
    int frequency;
    Node<T>* parent, *left, *right;

public:
    Node(T key, char character = '*', int frequency = INT_MAX) : key(key), character(character), frequency(frequency) {
        parent = left = right = nullptr;
    }

    Node(char character = '*', int frequency = INT_MAX, Node<T>* parent = nullptr, Node<T>* left = nullptr,
         Node<T>* right = nullptr)
         : character(character), frequency(frequency), parent(parent), left(left), right(right) {}

    ~Node() {
        delete left;
        delete right;
    }

    T get_key() { return key; }
    char get_character() { return character; }
    int get_frequency() { return frequency; }
    Node<T>*& get_left() { return left; }
    Node<T>*& get_right() { return right; }
    Node<T>*& get_parent() { return parent; }

    void set_key(T key) { this->key = key; }
    void set_character(char character) { this->character = character; }
    void set_frequency(int frequency) { this->frequency = frequency; }
    void set_left(Node<T>* left) { this->left = left; }
    void set_right(Node<T>* right) { this->right = right; }
    void set_parent(Node<T>* parent) { this->parent = parent; }

    void print(ostream& out = cout) {
        out << "(Key: " << key << " - Character: " << character << ")";

        out << " - Parent: ";
        if (parent)
            out << "(Key: " << parent->get_key() << " - Character: " << parent->get_character() << ")";
        else
            out << "(NULL)";

        out << " - Left: ";
        if (left)
            out << "(Key: " << left->get_key() << " - Character: " << left->get_character() << ")";
        else
            out << "(NULL)";

        out << " - Right: ";
        if (right)
            out << "(Key: " << right->get_key() << " - Character: " << right->get_character() << ")";
        else
            out << "(NULL)";

        out << endl;
    }

    bool is_leaf() { return !left && !right; }
};


template <typename T>
class BinarySearchTree {
private:
    Node<T>* root = nullptr;

    void insert_recursive(Node<T>*& start, Node<T>* node) {
        if (!start) {
            start = node;
            return;
        }

        if (node->get_key() < start->get_key()) {
            insert_recursive(start->get_left(), node);
            start->get_left()->set_parent(start);
        } else {
            insert_recursive(start->get_right(), node);
            start->get_right()->set_parent(start);
        }
    }

    void delete_subtree(Node<T>* node) {
        if (!node) return;

        delete_subtree(node->get_left());
        delete_subtree(node->get_right());
        delete node;
    }

    void inorder_visit(Node<T>* node, ostream& out) {
        if (!node) return;

        inorder_visit(node->get_left(), out);
        node->print(out);
        inorder_visit(node->get_right(), out);
    }

    void preorder_visit(Node<T>* node, ostream& out) {
        if (!node) return;

        node->print(out);
        preorder_visit(node->get_left(), out);
        preorder_visit(node->get_right(), out);
    }

    void postorder_visit(Node<T>* node, ostream& out) {
        if (!node) return;

        postorder_visit(node->get_left(), out);
        postorder_visit(node->get_right(), out);
        node->print(out);
    }

public:
    BinarySearchTree() {}

    BinarySearchTree(ifstream& input) { load(input); }

    ~BinarySearchTree() { delete_subtree(root); }

    Node<T>* get_root() { return root; }

    void load(ifstream& input) {
        input.clear(); // Pulisce eventuali flag di errore del file stream
        input.seekg(0, ios::beg); // Riporta il cursore del file all'inizio

        string line;
        while (getline(input, line)) { // Legge il file riga per riga

            // Se la riga inizia con '<', rimuove il primo carattere
            if (!line.empty() && line.front() == '<') 
                line.erase(0, 1);

            // Se la riga finisce con '>', rimuove l'ultimo carattere
            if (!line.empty() && line.back() == '>') 
                line.pop_back();

            // Cerca la posizione della virgola nella stringa
            size_t delim_pos = line.find(',');

            // Se non c'è la virgola, la riga è malformata → salta
            if (delim_pos == string::npos) 
                continue;

            // Estrae la parte della chiave come sottostringa
            string key_str = line.substr(0, delim_pos);

            // Estrae la parte del carattere dopo la virgola
            string char_str = line.substr(delim_pos + 1);

            T key;             // Variabile per salvare la chiave
            char character;    // Variabile per salvare il carattere

            // Converte la stringa della chiave nel tipo T (es. int, float...)
            istringstream(key_str) >> key;

            // Se la stringa del carattere non è vuota, prende il primo carattere
            character = !char_str.empty() ? char_str[0] : '*';

            // Crea un nuovo nodo con chiave e carattere, e lo inserisce nell'albero
            insert(new Node<T>(key, character));
        }
    }



    void insert(Node<T>* node) { insert_recursive(root, node); }

    void visit(VisitType type = inorder, Node<T>* node = nullptr, ostream& out = cout) {
        if (!node && !root) return;
        if (!node) node = root;

        string visit_type = type == inorder ? "INORDER" :
                            type == postorder ? "POSTORDER" : "PREORDER";

        out << visit_type << " visit" << endl;

        switch (type) {
            case preorder: {
                preorder_visit(node, out);
                break;
            }
            case postorder: {
                postorder_visit(node, out);
                break;
            }
            default: {
                inorder_visit(node, out);
                break;
            }
        }
    }

    Node<T>* tree_maximum(Node<T>* node) {
        while (node->get_right()) node = node->get_right();
        return node;
    }

    Node<T>* tree_minimum(Node<T>* node) {
        while (node->get_left()) node = node->get_left();
        return node;
    }

    Node<T>* predecessor(Node<T>* node) {
        if (!node) {
            cerr << "Invalid node for predecessor function" << endl;
            return nullptr;
        }

        if (node->get_left()) return tree_maximum(node->get_left());

        Node<T>* y = node->get_parent();
        while (y && node == y->get_left()) {
            node = y;
            y = y->get_parent();
        }

        return y;
    }

    Node<T>* successor(Node<T>* node) {
        if (!node) {
            cerr << "Invalid node for successor function" << endl;
            return nullptr;
        }

        if (node->get_right()) return tree_minimum(node->get_right());

        Node<T>* y = node->get_parent();
        while (y && node == y->get_right()) {
            node = y;
            y = y->get_parent();
        }

        return y;
    }

    void print_predecessor(Node<T>* node, ostream& out = cout) {
        Node<T>* pred = predecessor(node);

        if (!pred) {
            out << "No node predecessor for node ";
            node->print(out);
        } else {
            out << "Predecessor node for node ";
            node->print(out);
            out << '\t';
            pred->print(out);
        }

        out << endl;
    }

    void print_successor(Node<T>* node, ostream& out = cout) {
        Node<T>* succ = successor(node);

        if (!succ) {
            out << "No node successor for node ";
            node->print(out);
        } else {
            out << "Successor node for node ";
            node->print(out);
            out << '\t';
            succ->print(out);
        }

        out << endl;
    }

    Node<T>* search(Node<T>* node, T key) {
        if (!node || node->get_key() == key) return node;

        if (key < node->get_key()) return search(node->get_left(), key);
        return search(node->get_right(), key);
    }
};


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    BinarySearchTree<int> bst(in);
    bst.visit(preorder);

    cout << endl;
    bst.print_predecessor(bst.get_root());

    int key_search = 5;
    cout << endl << "Searching node with key " << key_search << "..." << endl;
    Node<int>* node_search = bst.search(bst.get_root(), key_search);
    if (node_search) {
        cout << "Node found => ";
        node_search->print();
    } else {
        cout << "Node not found" << endl;
    }

    in.close();
    out.close();

    return 0;
}
