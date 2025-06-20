#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <climits>
#include <set>
#include <fstream>

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
    int weight;
    Node* node1;
    Node* node2;
    string type;

public:
    Edge(Node* u, Node* v, int w) : node1(u), node2(v), weight(w), type("") {}

    int getWeight() { return weight; }
    Node* getSrc() { return node1; }
    Node* getDest() { return node2; }
    string getType() { return type; }

    void setType(string t) { type = t; }
};

class Graph {
private:
    vector<Node*> nodes;
    vector<Edge*> edges;
    int V, E, time, cycleCount;

    void DFS_VISIT(Node* node, vector<Node*>& path, int& cycleCount) {
        node->setColor(gray);                                      // Imposta il colore del nodo come GRAY (in esplorazione)
        time++;                                                    // Incrementa il tempo globale
        node->setDiscoveryTime(time);                              // Salva il tempo di scoperta del nodo
        path.push_back(node);                                      // Aggiunge il nodo al cammino attuale (per rilevamento cicli)

        for (Node* adj : node->getAdj()) {                         // Scorre tutti i nodi adiacenti
            Edge* edge = getEdge(node, adj);                       // Ottiene l'arco tra il nodo corrente e l'adiacente
            if (!edge) continue;                                   // Salta se l'arco non esiste (protezione da nullptr)

            if (adj->getColor() == white) {                        // Se il nodo adiacente non è stato visitato
                edge->setType(" DELL'ALBERO");                     // L'arco è di tipo "dell'albero"
                adj->setPredecessor(node);                         // Imposta il predecessore del nodo adiacente
                DFS_VISIT(adj, path, cycleCount);                  // Visita ricorsivamente il nodo adiacente

            } else if (adj->getColor() == gray) {                  // Se il nodo adiacente è in esplorazione (GRAY)
                edge->setType(" ALL'INDIETRO");                    // L'arco è "all'indietro" → c'è un ciclo

                cout << "Ciclo trovato: ";                         // Stampa messaggio per ciclo trovato
                int startIndex = -1;                               // Indice di inizio del ciclo nel path
                for (int i = 0; i < path.size(); i++) {            // Cerca il nodo adiacente nel path
                    if (path[i] == adj) {
                        startIndex = i;                            // Salva la posizione di inizio del ciclo
                        break;
                    }
                }
                if (startIndex != -1) {                            // Se trovato, stampa il ciclo
                    for (int i = startIndex; i < path.size(); i++)
                        cout << path[i]->getValue() << " ";        // Stampa i nodi nel ciclo
                    cout << adj->getValue() << endl;               // Chiude il ciclo stampando nuovamente il nodo iniziale
                    cycleCount++;                                  // Incrementa il numero di cicli trovati
                }

            } else if (adj->getColor() == black && node->getDiscoveryTime() < adj->getDiscoveryTime()) {   // Se il nodo è già visitato e il tempo di scoperta è maggiore
                    
                edge->setType(" IN AVANTI");                       // L'arco è "in avanti"

            } else if (adj->getColor() == black && node->getDiscoveryTime() > adj->getDiscoveryTime()) {    // Se il nodo è già visitato e il tempo di scoperta è minore
                    
                edge->setType(" TRASVERSALE");                     // L'arco è "trasversale"
            }
        }

        node->setColor(black);                                     // Termina l'esplorazione del nodo (BLACK)
        time++;                                                    // Incrementa il tempo globale
        node->setFinishTime(time);                                 // Salva il tempo di fine esplorazione
        path.pop_back();                                           // Rimuove il nodo dal cammino attuale
    }


public:
    Graph(int v, int e) : V(v), E(e), time(0), cycleCount(0) {}

    int getCycleCount() { return cycleCount; }

    void addNode(Node* node) {
        nodes.push_back(node);
        if (nodes.size() > V) {
            V = nodes.size();
        }
    }

    Node* getNode(int val) {
        for (auto& node : nodes) {
            if (node->getValue() == val)
                return node;
        }
        return nullptr;
    }

    void addEdge(Node* node1, Node* node2, int w) {
        edges.push_back(new Edge(node1, node2, w));
        node1->addAdj(node2);
        if (edges.size() > E)
            E = edges.size();
    }

    Edge* getEdge(Node* node1, Node* node2) {
        for (auto& edge : edges) {
            if (edge->getSrc() == node1 && edge->getDest() == node2) {
                return edge;
            }
        }
        return nullptr;
    }

    void DFS() {
        for (auto& node : nodes) {
            node->setColor(white);
            node->setPredecessor(nullptr);
        }

        vector<Node*> path;
        cycleCount = 0;

        for (auto& node : nodes) {
            if (node->getColor() == white) {
                DFS_VISIT(node, path, cycleCount);
            }
        }
    }

    void print(ofstream& out) {
        for (auto& node : nodes) {
            if (node->getPredecessor() == nullptr)
                out << "Node: " << node->getValue() << ", visit time: " << node->getFinishTime() - node->getDiscoveryTime() << ", predecessor : NULL" << endl;
            else
                out << "Node: " << node->getValue() << ", visit time: " << node->getFinishTime() - node->getDiscoveryTime() << ", predecessor: " << node->getPredecessor()->getValue() << endl;
        }
    }

    void printEdges() {
        for (auto& edge : edges) {
            cout << "L 'arco (" << edge->getSrc()->getValue() << "," << edge->getDest()->getValue() << ") e' un arco" << edge->getType() << endl;
        }
    }
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int V, E;
    in >> V >> E;

    Graph graph(V, E);

    for (int i = 0; i < V; i++)
        graph.addNode(new Node(i));

    for (int i = 0; i < E; i++) {
        int u, v, w;
        in >> u >> v >> w;

        Node* src = graph.getNode(u);
        Node* dest = graph.getNode(v);
        if (src != nullptr && dest != nullptr)
            graph.addEdge(src, dest, w);
        else
            cout << "Errore: nodo " << u << " o " << v << " non esistente!" << endl;
    }

    graph.DFS();
    graph.print(out);

    in.close();
    out.close();

    graph.printEdges();

    // stampa del numero di cicli trovati
    cout << "\nNumero di cicli trovati: " << graph.getCycleCount() << endl;

    return 0;
}
