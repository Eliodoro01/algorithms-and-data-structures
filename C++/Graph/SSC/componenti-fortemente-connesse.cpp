#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

enum Color { white, gray, black };

class Node {
private:
    int value;
    Node* predecessor;
    Color color;
    vector<Node*> adj;
    int discoveryTime;
    int finishTime;

public:
    Node(int val) : value(val), predecessor(nullptr), color(white), discoveryTime(INT_MAX), finishTime(INT_MAX) {}

    int getValue() { return value; }
    Node* getPredecessor() { return predecessor; }
    Color getColor() { return color; }
    int getDiscoveryTime() { return discoveryTime; }
    int getFinishTime() { return finishTime; }
    vector<Node*>& getAdj() { return adj; }

    void setColor(Color c) { color = c; }
    void addAdj(Node* n) { adj.push_back(n); }
    void setPredecessor(Node* n) { predecessor = n; }
    void setDiscoveryTime(int d) { discoveryTime = d; }
    void setFinishTime(int f) { finishTime = f; }
};

class Edge {
private:
    Node* src;
    Node* dest;
    int weight;

public:
    Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w) {}

    Node* getSrc() { return src; }
    Node* getDest() { return dest; }
    int getWeight() { return weight; }

    void setSrc(Node* u) { src = u; }
    void setDest(Node* v) { dest = v; }
};

class Graph {
private:
    vector<Node*> nodes;
    vector<Edge*> edges;
    int V, E, time;

    void DFS_VISIT(Node* node) {
        node->setColor(gray);
        time++;
        node->setDiscoveryTime(time);

        for (auto& adj : node->getAdj()) {
            if (adj->getColor() == white) {
                adj->setPredecessor(node);
                DFS_VISIT(adj);
            }
        }

        node->setColor(black);
        time++;
        node->setFinishTime(time);
    }

public:
    Graph(int v, int e) : V(v), E(e), time(0) {}

    void insertNode(Node* node) {
        nodes.push_back(node);
        if (nodes.size() > V) {
            V = nodes.size();
        }
    }

    void insertEdge(Node* src, Node* dest, int weight) {
        edges.push_back(new Edge(src, dest, weight));
        if (edges.size() > E) {
            E = edges.size();
        }
    }

    Node* getNode(int key) {
        for (auto& node : nodes) {
            if (node->getValue() == key) {
                return node;
            }
        }
        return nullptr;
    }

    void DFS() {
        for (auto& node : nodes) {
            node->setColor(white);
            node->setPredecessor(nullptr);
        }

        time = 0;

        for (auto& node : nodes) {
            if (node->getColor() == white) {
                DFS_VISIT(node);
            }
        }
    }

    // Restituisce il grafo trasposto (inversione degli archi)
    Graph* getTranspose() {
        Graph* gt = new Graph(V, E);
        vector<Node*> newNodes(V, nullptr);

        // Crea nuovi nodi
        for (auto& node : nodes) {
            Node* newNode = new Node(node->getValue());
            newNodes[node->getValue()] = newNode;
            gt->insertNode(newNode);
        }

        // Crea archi invertiti e aggiorna le adiacenze
        for (auto& edge : edges) {
            int srcVal = edge->getSrc()->getValue();
            int destVal = edge->getDest()->getValue();

            Node* newSrc = newNodes[destVal]; // invertito
            Node* newDest = newNodes[srcVal];

            gt->insertEdge(newSrc, newDest, edge->getWeight());
            newSrc->addAdj(newDest); // costruisce la lista di adiacenza corretta
        }

        return gt;
    }

    void fillOrder(Node* node, vector<Node*>& stack) {
        node->setColor(gray);
        for (auto& adj : node->getAdj()) {
            if (adj->getColor() == white) {
                fillOrder(adj, stack);
            }
        }
        node->setColor(black);
        stack.push_back(node);
    }

    void DFSUtil(Node* node, vector<bool>& visited) {
        cout << node->getValue() << " ";
        visited[node->getValue()] = true;
        for (auto& adj : node->getAdj()) {
            if (!visited[adj->getValue()]) {
                DFSUtil(adj, visited);
            }
        }
    }

    void printStronglyConnectedComponents() {
        vector<Node*> stack;
        for (auto& node : nodes) {
            node->setColor(white);
        }
        for (auto& node : nodes) {
            if (node->getColor() == white) {
                fillOrder(node, stack);
            }
        }

        Graph* gt = getTranspose();

        vector<bool> visited(V, false);
        cout << "Componenti fortemente connesse:\n";
        while (!stack.empty()) {
            Node* n = stack.back();
            stack.pop_back();

            Node* transposedNode = gt->getNode(n->getValue());

            if (!visited[transposedNode->getValue()]) {
                gt->DFSUtil(transposedNode, visited);
                cout << endl;
            }
        }

        delete gt;
    }
};

int main() {
    ifstream input("input.txt");
    if (!input.is_open()) {
        cerr << "Errore nell'apertura del file di input.\n";
        return 1;
    }

    int V, E;
    input >> V >> E;

    Graph g(V, E);

    for (int i = 0; i < V; ++i) {
        g.insertNode(new Node(i));
    }

    for (int i = 0; i < E; ++i) {
        int u, v, w;
        input >> u >> v >> w;

        Node* src = g.getNode(u);
        Node* dest = g.getNode(v);

        g.insertEdge(src, dest, w); 
        src->addAdj(dest);
    }

    input.close();

    g.printStronglyConnectedComponents();

    return 0;
}
