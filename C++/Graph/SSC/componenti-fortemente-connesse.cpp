#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

enum Color{white, gray, black};

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

class Edge{

    private:
        Node* src;
        Node* dest;
        int weight;

    public:
        Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w){}

        Node* getSrc(){return src;}
        Node* getDest(){return dest;}
        int getWeight(){return weight;}

        void setSrc(Node* u){src = u;}
        void setDest(Node* v){dest = v;}

};

class Graph{

    private:
        vector<Node*>nodes;
        vector<Edge*>edges;
        int V, E, time;

        void DFS_VISIT(Node* node){

            node->setColor(gray);
            time++;
            node->setDiscoveryTime(time);

            for(auto& adj : node->getAdj()){
                if(adj->getColor() == white){
                    adj->setPredecessor(node);
                    DFS_VISIT(adj);
                }
            }

            node->setColor(black);
            time++;
            node->setFinishTime(time);
        }

    public:
        Graph(int v, int e) : V(v), E(e){}

        void insertNode(Node* node){
            nodes.push_back(node);

            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        void insertEdge(Node* src, Node* dest, int weight){

            edges.push_back(new Edge(src, dest, weight));

            if(edges.size() > E){
                E = edges.size();
            }
        }

        Node* getNode(int key){
            for(auto& node : nodes){
                if(node->getValue() == key){
                    return node;
                }
            }
            return nullptr;
        }

        Edge* getEdge(Node* u, Node* v){

            for(auto& edge : edges){
                if(edge->getSrc() == u && edge->getDest() == v){
                    return edge;
                }
            }
            return nullptr;
        }

        void DFS(){

            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
            }

            for(auto& node : nodes){
                if(node->getColor() == white){
                    DFS_VISIT(node);
                }
            }
        }

/*********************************************************************************************/

        // Restituisce il grafo trasposto (inversione degli archi)
        Graph* getTranspose() {
            Graph* gt = new Graph(V, E);
            
            // Crea tutti i nodi nel nuovo grafo
            for (auto& node : nodes) {
                gt->insertNode(new Node(node->getValue()));
            }

            // Aggiunge gli archi invertiti
            for (auto& edge : edges) {
                Node* newSrc = gt->getNode(edge->getDest()->getValue());
                Node* newDest = gt->getNode(edge->getSrc()->getValue());
                gt->insertEdge(newSrc, newDest, edge->getWeight());
                newSrc->addAdj(newDest);
            }

            return gt;
        }

        // DFS modificata per accumulare nodi in ordine di fine visita
        void fillOrder(Node* node, vector<Node*>& stack) {
            node->setColor(gray);
            for (auto& adj : node->getAdj()) {
                if (adj->getColor() == white) {
                    fillOrder(adj, stack);
                }
            }
            node->setColor(black);
            stack.push_back(node); // Inserimento post-visita
        }

        // Stampa una singola componente connessa
        void DFSUtil(Node* node, vector<bool>& visited) {
            cout << node->getValue() << " ";
            visited[node->getValue()] = true;
            for (auto& adj : node->getAdj()) {
                if (!visited[adj->getValue()]) {
                    DFSUtil(adj, visited);
                }
            }
        }

        // Funzione principale per stampare le SCC
        void printStronglyConnectedComponents() {
            // Step 1: Ordina i nodi per tempo di fine visita decrescente
            vector<Node*> stack;
            for (auto& node : nodes) {
                node->setColor(white);
            }
            for (auto& node : nodes) {
                if (node->getColor() == white) {
                    fillOrder(node, stack);
                }
            }

            // Step 2: Trasponi il grafo
            Graph* gt = getTranspose();

            // Step 3: Visita i nodi in ordine decrescente di finish time
            vector<bool> visited(V, false);
            cout << "Componenti fortemente connesse:\n";
            while (!stack.empty()) {
                Node* n = stack.back();
                stack.pop_back();
                Node* transposedNode = gt->getNode(n->getValue());

                if (!visited[transposedNode->getValue()]) {
                    DFSUtil(transposedNode, visited);
                    cout << endl;
                }
            }

            delete gt;
        }

};


