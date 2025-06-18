#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <algorithm>

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

using namespace std;

class Node {
    private:
        int val;
        int color;
        Node* predecessor;
        int distance;
        vector<Node*> adj;

    public:
        Node(int val) : val(val), color(WHITE), predecessor(nullptr), distance(INT_MAX) {}

        int getVal() { return val; }
        int getColor() { return color; }
        Node* getPredecessor() { return predecessor; }
        int getDistance() { return distance; }
        vector<Node*>& getAdjacents() { return adj; }

        void setColor(int c) { color = c; }
        void setPredecessor(Node* n) { predecessor = n; }
        void setDistance(int dist) { distance = dist; }
        void addAdj(Node* n) { adj.push_back(n); }
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
};
class Graph {
    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E;

        struct compare {
            bool operator()(Node* u, Node* v) {
                return u->getDistance() > v->getDistance();
            }
        };

    public:
        Graph(int v, int e) : V(v), E(e) {}

        void addNode(Node* node) {
            nodes.push_back(node);

            if (nodes.size() > V)
                V = nodes.size();
        }

        Node* getNode(int val) {
            for (auto& node : nodes) {
                if (node->getVal() == val)
                    return node;
            }

            return nullptr;
        }

        void addEdge(Node* u, Node* v, int w) {
            edges.push_back(new Edge(u,v,w));
            u->addAdj(v);
            v->addAdj(u);

            if (edges.size() > E)
                E = edges.size();
        }

        Edge* getEdge(Node* u, Node* v) {
            for (auto& edge : edges) {
                if ( (edge->getSrc() == u && edge->getDest() == v) || (edge->getSrc() == v && edge->getDest() == u) )
                    return edge;
            }

            return nullptr;
        }

        void BFS(Node* s, ofstream& out) {
            for(auto& u : nodes) {
                u->setColor(WHITE);
                u->setPredecessor(nullptr);
                u->setDistance(INT_MAX);
            }

            s->setColor(GRAY);
            s->setDistance(0);

            queue<Node*> q;
            q.push(s);

            while (!q.empty()) {
                Node* u = q.front();
                q.pop();

                for (Node* v : u->getAdjacents()) {
                    if (v->getColor() == WHITE) {
                        v->setColor(GRAY);
                        v->setPredecessor(u);
                        v->setDistance(u->getDistance() + 1); // u->getDistance() + getEdgeWeight(u,v)
                        q.push(v);
                    }
                }

                u->setColor(BLACK);
            }

            for (auto& node : nodes) {
                if (node->getPredecessor() == nullptr)
                    out << "Node: " << node->getVal() << " -> (predecessor: NULL, distance: " << node->getDistance() << ")" << endl;
                else
                    out << "Node: " << node->getVal() << " -> (predecessor: " << node->getPredecessor()->getVal()
                        << ", distance: " << node->getDistance() << ")" << endl;
            }
        }


        void prim(Node* s) {
            for (auto& u : nodes) {
                u->setPredecessor(nullptr);
                u->setDistance(INT_MAX);
            }

            s->setDistance(0);
            vector<bool> inMST(V, false);
            priority_queue<Node*, vector<Node*>, compare> minPQ;
            minPQ.push(s);

            while (!minPQ.empty()) {
                Node* u = minPQ.top();
                minPQ.pop();
                inMST[u->getVal()] = true;

                for(Node* v : u->getAdjacents()) {
                    Edge* edge = getEdge(u,v);

                    if (!inMST[v->getVal()] && edge->getWeight() < v->getDistance()) {
                        v->setDistance(edge->getWeight());
                        v->setPredecessor(u);
                        minPQ.push(v);
                    }
                }
            }
        }

        void printMST() {
            cout << "\nMinimum Spanning Tree:" << endl;
            for (auto& node : nodes) {
                if (node->getPredecessor() == nullptr)
                    cout << "Node: " << node->getVal() << " -> (predecessor: NULL, distance from predecessor: "
                        << node->getDistance() << ")" << endl;
                else
                    cout << "Node: " << node->getVal() << " -> (predecessor: " << node->getPredecessor()->getVal()
                        << ", distance from predecessor: " << node->getDistance() << ")" << endl;
            }
        }

        bool isBinary() {
            for (auto& u : nodes) {
                int childCount = 0;

                for(Node* v : u->getAdjacents()) {
                    if (v != u->getPredecessor())
                        childCount++;
                }

                if (childCount > 2)
                    return false;
            }

            return true;
        }

        bool isCompleteBinary() {
            bool isLeaf = false;

            for (auto& u : nodes) {
                vector<Node*> children;

                for(Node* v : u->getAdjacents()) {
                    if (v != u->getPredecessor())
                        children.push_back(v);
                }

                if (children.size() < 2)
                    isLeaf = true;

                if (isLeaf && !children.empty())
                    return false;
            }

            return true;
        }
};


int main() {
    ifstream in("input.txt");
    ofstream out ("output.txt");

    int V, E;
    in >> V >> E;

    Graph graph(V, E);

    for (int i=0; i<V; i++)
        graph.addNode(new Node(i));

    for (int i=0; i<E; i++) {
        int u, v, w;
        in >> u >> v >> w;

        Node* src = graph.getNode(u);
        Node* dest = graph.getNode(v);

        if (src != nullptr && dest != nullptr)
            graph.addEdge(src, dest, w);
        else
            cout << "Non e' stato possibile aggiungere l'arco poiche' il nodo " << u << " e/o il nodo " << v << " non esistono!" << endl;
    }

    Node* source = graph.getNode(0);
    if (source != nullptr)
        graph.BFS(source, out);
    else
        cout << "Non e' stato possibile effettuare la BFS poiche' il nodo sorgente passato in input non esiste!" << endl;

    in.close();
    out.close();

    if (graph.isCompleteBinary())
        cout << "\nL'albero BF e' un albero binario completo!" << endl;
    else
        cout << "\nL'albero BF non è un albero binario completo!" << endl;

    source = graph.getNode(0);
    if (source != nullptr) {
        graph.prim(source);
        graph.printMST();
    }
    else
        cout << "Non e' stato possibile eseguire il metodo di Prim poiche' il nodo sorgente passato in input non esiste!" << endl;

    if (graph.isBinary())
        cout << "\nIl MST è un albero binario!" << endl;
    else
        cout << "\nIl MST non è un albero binario!" << endl;
}