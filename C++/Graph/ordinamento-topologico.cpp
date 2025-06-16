#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <stack>
#include <set>
#include <algorithm>
#include <queue>

const int WHITE = 0;
const int GRAY = 1;
const int BLACK = 2;

using namespace std;

class Node {
    private:
        int val;
        int color;
        Node* predecessor;
        int discoveryTime;
        int finishTime;
        int distance;
        vector<Node*> adj;

    public:
        Node(int val) : val(val), color(WHITE), predecessor(nullptr), discoveryTime(INT_MAX), finishTime(INT_MAX) {}

        int getVal() { return val; }
        int getColor() { return color; }
        Node* getPredecessor() { return predecessor; }
        int getDiscoveryTime() { return discoveryTime; }
        int getFinishTime() { return finishTime; }
        int getDistance() { return distance; }
        vector<Node*>& getAdjacents() { return adj; }

        void setColor(int c) { color = c; }
        void setPredecessor(Node* n) { predecessor = n; }
        void setDiscoveryTime(int time) { discoveryTime = time; }
        void setFinishTime(int time) { finishTime = time; }
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
        int V, E, time;
        stack<Node*> L;

        void DFS_VISIT(Node* u) {
            u->setColor(GRAY);
            time++;
            u->setDiscoveryTime(time);

            for (Node* v : u->getAdjacents()) {

                if (v->getColor() == WHITE) {
                    v->setPredecessor(u);
                    DFS_VISIT(v);
                }
            }

            u->setColor(BLACK);
            time++;
            u->setFinishTime(time);
            L.push(u);
        }

        bool isSafe(Node* v, vector<Node*>& path, int pos) {
            Node* lastNode = path[pos-1];
            bool isAdjacent = false;

            for (Node* adjNode : lastNode->getAdjacents()) {
                if (adjNode == v) {
                    isAdjacent = true;
                    break;
                }
            }

            if (!isAdjacent)
                return false;

            for (int i=0; i<pos; i++) {
                if (path[i] == v)
                    return false;
            }

            return true;
        }

        bool hamiltonianCycle(vector<Node*>& path, int pos) {
            if (pos == V) {
                Node* lastNode = getNode(pos-1);

                for (Node* adjNode : lastNode->getAdjacents()) {
                    if (adjNode == path[0])
                        return true;
                }

                return false;
            }

            for (auto& v : nodes) {
                if (isSafe(v, path, pos)) {
                    path[pos] = v;

                    if (hamiltonianCycle(path, pos+1))
                        return true;

                    path[pos] = nullptr;
                }
            }

            return false;
        }

        void initializeSingleSource(Node* s) {
            for (auto& u : nodes) {
                u->setDistance(INT_MAX);
                u->setPredecessor(nullptr);
            }
            s->setDistance(0);
            s->setPredecessor(nullptr);
        }

        void relax(Edge* edge) {
            if (edge->getDest()->getDistance() > edge->getSrc()->getDistance() + edge->getWeight()) {
                edge->getDest()->setDistance(edge->getSrc()->getDistance() + edge->getWeight());
                edge->getDest()->setPredecessor(edge->getSrc());
            }
        }

        struct compare {
            bool operator()(Node* u, Node* v) {
                return u->getDistance() > v->getDistance();
            }
        };

    public:
        Graph(int v, int e) : V(v), E(e), time(0) {}

        void addNode(Node* n) {
            nodes.push_back(n);

            if (nodes.size() > V)
                V = nodes.size();
        }

        void addEdge(Node* u, Node* v, int w) {
            edges.push_back(new Edge(u,v,w));
            u->addAdj(v);

            if (edges.size() > E)
                E = edges.size();
        }

        Node* getNode(int val) {
            for (auto& node : nodes) {
                if (node->getVal() == val)
                    return node;
            }

            return nullptr;
        }

        Edge* getEdge(Node* u, Node* v) {
            for (auto& edge: edges) {
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

            time++;

            for (auto& u : nodes) {
                if (u->getColor() == WHITE) {
                    DFS_VISIT(u);
                }
            }
        }

        void topologicalPrint(ofstream& out) {
            while (!L.empty()) {
                Node* node = L.top();
                L.pop();
                out << node->getVal() << endl;
            }
        }

        bool findHamiltonianCycle(int pos) {
            vector<Node*> path(V, nullptr);
            path[0] = getNode(pos);

            if (hamiltonianCycle(path, pos+1)) {
                cout << "\nCiclo Hamiltoniano trovato: ";

                for (int i=0; i<V; i++) {
                    cout << path[i]->getVal() << " ";
                }
                cout << path[0]->getVal() << endl;

                return true;
            } else {
                cout << "\nNon esiste un ciclo Hamiltoniano!" << endl;

                return false;
            }
        }

        void bellmanFord(Node* s, Node* d) {
            initializeSingleSource(s);

            for (int i=0; i<V; i++) {
                for (auto& edge : edges)
                    relax(edge);
            }

            vector<int> path;
            Node* n = d;
            while (n != nullptr) {
                path.push_back(n->getVal());
                n = n->getPredecessor();
            }

            cout << "\nDistanza tra il nodo " << s->getVal() << " e il nodo " << d->getVal() << ": " << d->getDistance();

            cout << "\nCammino di peso minimo: ";
            for (int i=path.size()-1; i>=0; i--) {
                cout << path[i] << " ";
            }
            cout << endl << endl;
        }

        void dijkstra(Node* s) {
            initializeSingleSource(s);

            priority_queue<Node*, vector<Node*>, compare> minPQ;
            minPQ.push(s);

            set<Node*> visited;

            while(!minPQ.empty()) {
                Node* u = minPQ.top();
                minPQ.pop();

                if (visited.find(u) != visited.end())
                    continue;

                visited.insert(u);

                for (Node* v : u->getAdjacents()) {
                    Edge* edge = getEdge(u,v);

                    if (edge != nullptr) {
                        relax(edge);

                        if (visited.find(v) == visited.end())
                            minPQ.push(v);
                    }
                }
            }

            cout << "\nDistanze minime dal nodo " << s->getVal() << ":" << endl;
            for (auto& u : nodes)
                cout << "Node: " << u->getVal() << ", distance: " << u->getDistance() << endl;
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
            cout << "Non e' stato possibile aggiungere l'arco poiche' il nodo " << u << " e/o il nodo " << v << " non esistono!" << endl;
    }

    graph.DFS();
    graph.topologicalPrint(out);

    in.close();
    out.close();

    graph.findHamiltonianCycle(0);

    Node* s = graph.getNode(0);
    Node* d = graph.getNode(3);

    if (s != nullptr && d != nullptr)
        graph.bellmanFord(s, d);
    else
        cout << "\nNon e' stato possibile invocare il metodo di Bellman Ford in quanto il nodo 0 e/o il nodo 3 non esistono!" << endl;

    s = graph.getNode(0);
    if (s != nullptr)
        graph.dijkstra(s);
    else
        cout << "\nNon e' stato possibile invocare il metodo di Dijkstra in quanto il nodo 0 non esiste!" << endl;

    return 0;
}