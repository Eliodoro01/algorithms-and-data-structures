#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>
#include <sstream>

using namespace std;

enum Color { white, gray, black };

class Node {
private:
    Color color;
    Node* predecessor;
    vector<Node*> adj;
    int distance;
    int value;

public:
    Node(int value) : value(value), predecessor(nullptr), color(white), distance(INT_MAX) {}

    int getValue() { return value; }
    int getDistance() { return distance; }
    Color getColor() { return color; }
    vector<Node*> getAdj() { return adj; }
    Node* getPredecessor() { return predecessor; }

    void setAdj(Node* adia) { adj.push_back(adia); }
    void setPredecessor(Node* pred) { predecessor = pred; }
    void setColor(Color col) { color = col; }  // ✅ CORRETTO
    void setDistance(int d) { distance = d; }
};

class Edge {
private:
    Node* src;
    Node* dest;
    int weights;

public:
    Edge(Node* u, Node* v, int w) : src(u), dest(v), weights(w) {}

    Node* getSrc() { return src; }
    Node* getDest() { return dest; }
    int getWeights() { return weights; }

    void setSrc(Node* u) { src = u; }
    void setDest(Node* v) { dest = v; }
    void setWeights(int w) { weights = w; }
};

class Graph {
private:
    vector<Node*> nodes;
    vector<Edge*> edges;
    int V, E;

public:
    Graph(int v = 0, int e = 0) : V(v), E(e) {}

    Node* getNode(int value) {
        for (auto& node : nodes) {
            if (node->getValue() == value)
                return node;
        }
        return nullptr;
    }

    Edge* getEdge(Node* src, Node* dest) {
        for (auto& edge : edges) {
            if (edge->getSrc() == src && edge->getDest() == dest)
                return edge;
        }
        return nullptr;
    }

    void addEdge(Node* src, Node* dest, int weight) {
        edges.push_back(new Edge(src, dest, weight));
        src->setAdj(dest);
        dest->setAdj(src); // se grafo orientato, togli questa
        if (edges.size() > E) E = edges.size();
    }

    void addNode(Node* node) {
        nodes.push_back(node);
        if (nodes.size() > V) V = nodes.size();
    }

    void BFS(Node* src, ofstream& out) {
        for (auto& node : nodes) {
            node->setColor(white);
            node->setPredecessor(nullptr);
            node->setDistance(INT_MAX);
        }

        src->setDistance(0);
        src->setColor(gray);

        queue<Node*> q;
        q.push(src);

        while (!q.empty()) {
            Node* node = q.front();
            q.pop();

            for (auto& adj : node->getAdj()) {
                if (adj->getColor() == white) {
                    adj->setPredecessor(node);
                    adj->setDistance(node->getDistance() + 1);
                    adj->setColor(gray);
                    q.push(adj);
                }
            }

            node->setColor(black);
        }

        for (auto& node : nodes) {
            if (node->getPredecessor() == nullptr) {
                out << "Node: " << node->getValue() << " -> (predecessor: NULL, distance: " << node->getDistance() << ")" << endl;
            } else {
                out << "Node: " << node->getValue()
                    << " -> (predecessor: " << node->getPredecessor()->getValue()
                    << ", distance: " << node->getDistance() << ")" << endl;
            }
        }
    }

    void loadFromFile(ifstream& input) {
        int totalNodes, totalEdges;
        string headerLine;

        getline(input, headerLine);
        if (headerLine.front() == '<') headerLine = headerLine.substr(1);
        if (headerLine.back() == '>') headerLine.pop_back();
        for (char& c : headerLine) if (c == ',') c = ' ';

        istringstream headerStream(headerLine);
        headerStream >> totalNodes >> totalEdges;

        for (int i = 0; i < totalNodes; i++)
            addNode(new Node(i));

        string line;
        while (getline(input, line)) {
            if (line.front() == '<') line = line.substr(1);
            if (line.back() == '>') line.pop_back();
            for (char& c : line) if (c == ',') c = ' ';

            istringstream edgeStream(line);
            int srcVal, destVal, weight;
            edgeStream >> srcVal >> destVal >> weight;

            Node* src = getNode(srcVal);
            Node* dest = getNode(destVal);
            if (src && dest)
                addEdge(src, dest, weight);
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    if (!in.is_open()) {
        cerr << "Errore nell'apertura del file input.txt" << endl;
        return 1;
    }

    Graph graph;
    graph.loadFromFile(in);

    Node* start = graph.getNode(0); // nodo di partenza

    if (start != nullptr) {
        graph.BFS(start, out);
    } else {
        cerr << "Nodo di partenza non trovato." << endl;
    }

    in.close();
    out.close();
    return 0;
}
