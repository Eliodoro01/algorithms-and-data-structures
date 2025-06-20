#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Node {
    private:
        int key;
        char character;
        Node* left;
        Node* right;
        Node* parent;

    public:
        Node(int k, char c) : key(k), character(c), left(nullptr), right(nullptr), parent(nullptr) {}

        int getKey() { return key; };
        char getCharacter() { return character; }
        Node* getLeft() { return left; }
        Node* getRight() { return right; }
        Node* getParent() { return parent; }

        void setLeft(Node* n) { left = n; }
        void setRight(Node* n) { right = n; }
        void setParent(Node* n) { parent = n; }
};

class ABR {
    private:
        Node* root;
        unordered_map<char, string> huffmanTable;

        void buildHuffmanTable(Node* node, string path) {
            if (node == nullptr)
                return;

            if (node->getLeft() == nullptr && node->getRight() == nullptr && node->getCharacter() != '*')
                huffmanTable[node->getCharacter()] = path;

            buildHuffmanTable(node->getLeft(), path + "0");
            buildHuffmanTable(node->getRight(), path + "1");
        }

        Node* insertRec(Node* node, int key, char character) {
            if (node == nullptr)
                return new Node(key, character);

            if (key < node->getKey()) {
                Node* leftChild = insertRec(node->getLeft(), key, character);
                node->setLeft(leftChild);
                leftChild->setParent(node);
            }
            else {
                Node* rightChild = insertRec(node->getRight(), key, character);
                node->setRight(rightChild);
                rightChild->setParent(node);
            }

            return node;
        }

        void preorderRec(Node* node, ofstream& out) {
            if (node == nullptr)
                return;

            out << "Key: " << node->getKey() << ", character: " << node->getCharacter() << endl;
            preorderRec(node->getLeft(), out);
            preorderRec(node->getRight(), out);
        }

        Node* minimum(Node* x) {
            while (x->getLeft() != nullptr)
                x = x->getLeft();
            return x;
        }

        Node* maximum(Node* x) {
            while (x->getRight() != nullptr)
                x = x->getRight();
            return x;
        }

    public:
        ABR() : root(nullptr) {}

        Node* getRoot() { return root; }

        void insert(int key, char character) { root = insertRec(root, key, character); }
        void preorder(ofstream& out) { preorderRec(root, out); }

        Node* search(Node* node, int key) {
            if (node == nullptr || node->getKey() == key)
                return node;

            if (key < node->getKey())
                return search(node->getLeft(), key);
            else
                return search(node->getRight(), key);
        }

        Node* getSuccessor(Node* x) {
            if (x == nullptr)
                return nullptr;

            if (x->getRight() != nullptr)
                return minimum(x->getRight());

            Node* y = x->getParent();
            while (y != nullptr && x == y->getRight()) {
                x = y;
                y = y->getParent();
            }

            return y;
        }

        void writeSuccessor(Node* x, ofstream& out) {
            Node* succ = getSuccessor(x);

            if (succ != nullptr)
                out << "Successor's key: " << succ->getKey() << ", successor's character: " << succ->getCharacter() << endl;
            else
                out << "This node doesn't have a successor!" << endl;
        }

        Node* getPredecessor(Node* x) {
            if (x == nullptr)
                return nullptr;

            if (x->getLeft() != nullptr)
                return maximum(x->getLeft());

            Node* y = x->getParent();
            while (y != nullptr && x == y->getLeft()) {
                x = y;
                y = y->getParent();
            }

            return y;
        }

        void writePredecessor(Node* x, ofstream& out) {
            Node* pred = getPredecessor(x);

            if (pred != nullptr)
                out << "Predecessor's key: " << pred->getKey() << ", predecessor's character: " << pred->getCharacter() << endl;
            else
                out << "This node doesn't have a predecessor!" << endl;
        }

        void generateHuffmanTable() {
            buildHuffmanTable(root, "");
        }

        string encodeString(string input) {
            string encoded;
            for (char c : input) {
                if (huffmanTable.find(c) != huffmanTable.end())
                    encoded += huffmanTable[c];
                else {
                    cout << "Il carattere non e' stato trovato!" << endl;
                    return "";
                }
            }

            return encoded;
        }

        string decodeString(string encoded) {
            string decoded;
            Node* currentNode = root;

            for (char bit : encoded) {
                if (bit == '0')
                    currentNode = currentNode->getLeft();
                else if (bit == '1')
                    currentNode = currentNode->getRight();

                if (currentNode->getLeft() == nullptr && currentNode->getRight() == nullptr) {
                    decoded += currentNode->getCharacter();
                    currentNode = root;
                }
            }

            return decoded;
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
