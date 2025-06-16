#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <set>

using namespace std;

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

class Node {
    private:
        int val;
        int color;
        Node* predecessor;
        int discoveryTime;
        int finishTime;
        vector<Node*> adj;

    public:
        Node(int val) : val(val), color(WHITE), predecessor(nullptr), discoveryTime(INT_MAX), finishTime(INT_MAX) {}

        int getVal() { return val; }
        int getColor() { return color; }
        Node* getPredecessor() { return predecessor; }
        int getDiscoveryTime() { return discoveryTime; }
        int getFinishTime() { return finishTime; }
        vector<Node*>& getAdjacents() { return adj; }

        void setColor(int c) { color = c; }
        void setPredecessor(Node* n) { predecessor = n; }
        void setDiscoveryTime(int time) { discoveryTime = time; }
        void setFinishTime(int time) { finishTime = time; }
        void addAdj(Node* n) { adj.push_back(n); }
};

class Edge {
    private:
        Node* src;
        Node* dest;
        int weight;
        string type;

    public:
        Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w) {}

        Node* getSrc() { return src; }
        Node* getDest() { return dest; }
        int getWeight() { return weight; }
        string getType() { return type; }

        void setType(string s) { type = s; }
};

class Graph {
    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E, time, cycleCount;

        void DFS_VISIT(Node* u) {
            u->setColor(GRAY);
            time++;
            u->setDiscoveryTime(time);


            for (Node* v : u->getAdjacents()) {
                Edge* edge = getEdge(u,v);

                if (v->getColor() == WHITE) {
                    edge->setType("DELL'ALBERO");
                    v->setPredecessor(u);
                    DFS_VISIT(v);
                }
                else if (v->getColor() == GRAY)
                    edge->setType("ALL'INDIETRO");
                else if (v->getColor() == BLACK && u->getDiscoveryTime() < v->getDiscoveryTime())
                    edge->setType("IN AVANTI");
                else if (v->getColor() == BLACK && u->getDiscoveryTime() > v->getDiscoveryTime())
                    edge->setType("TRASVERSALE");
            }

            u->setColor(BLACK);
            time++;
            u->setFinishTime(time);
        }

        void cyclesRec(Node* u, set<Node*>& visited, vector<Node*>& path) {
            u->setColor(GRAY);
            visited.insert(u);
            path.push_back(u);

            for (Node* v : u->getAdjacents()) {
                if (v->getColor() == WHITE) {
                    v->setPredecessor(u);
                    cyclesRec(v, visited, path);
                } else if (v->getColor() == GRAY) {
                    cout << "Ciclo trovato: ";

                    int startIndex = -1;

                    for (int i=0; i<path.size(); i++) {
                        if (path[i] == v) {
                            startIndex = i;
                            break;
                        }
                    }

                    if (startIndex != -1) {
                        for (int i=startIndex; i<path.size(); i++) {
                            cout << path[i]->getVal() << " ";
                        }
                        cout << v->getVal() << endl;

                        cycleCount++;
                    }
                }
            }

            u->setColor(BLACK);
            path.pop_back();
        }

    public:
        Graph(int v, int e) : V(v), E(e), time(0), cycleCount(0) {}

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

            if (edges.size() > E)
                E = edges.size();
        }

        Edge* getEdge(Node* u, Node* v) {
            for (auto& edge : edges) {
                if (edge->getSrc() == u && edge->getDest() == v)
                    return edge;
            }

            return nullptr;
        }

        void DFS() {
            for (auto& u : nodes) {
                u->setColor(WHITE);
                u->setPredecessor(nullptr);
            }

            for (auto& u : nodes) {
                if (u->getColor() == WHITE)
                    DFS_VISIT(u);
            }
        }

        void print(ofstream& out) {
            for (auto& node : nodes) {
                if (node->getPredecessor() == nullptr)
                    out << "Node: " << node->getVal() << ", visit time: " << node->getFinishTime() - node->getDiscoveryTime()
                        << ", predecessor: NULL" << endl;
                else
                    out << "Node: " << node->getVal() << ", visit time: " << node->getFinishTime() - node->getDiscoveryTime()
                        << ", predecessor: " << node->getPredecessor()->getVal() << endl;
            }
        }

        void printEdges() {
            for (auto& edge : edges) {
                cout << "L'arco (" << edge->getSrc()->getVal() << "," << edge->getDest()->getVal() << ") e' un arco "
                    << edge->getType() << endl;
            }
        }

        void printCycles() {
            set<Node*> visited;
            vector<Node*> path;

            for (auto& u : nodes) {
                u->setColor(WHITE);
                u->setPredecessor(nullptr);
            }

            for (auto& u : nodes) {
                if (u->getColor() == WHITE) {
                    cyclesRec(u, visited, path);
                }
            }

            cout << "\nNumero cicli: " << cycleCount << endl;
        }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

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
            cout << "Non e' stato possibile aggiungere l'arco poiche' il nodo " << u << " e/o il nodo " << v
                << " non esistono!" << endl;
    }

    graph.DFS();
    graph.print(out);

    in.close();
    out.close();

    graph.printEdges();
    graph.printCycles();

    return 0;
}