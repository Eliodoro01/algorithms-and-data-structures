#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>
#include <climits>
#include <fstream>
#include <queue>
#include <set>

using namespace std;

 enum Color{white, gray, black};

class Node{

    private:
        int value;
        Node* predecessor;
        Color color;
        vector<Node*> adj;
        int discoveryTime;
        int finishDiscoveryTime;
        int distance;

    public:
        Node(int val) : value(val), predecessor(nullptr), color(white), discoveryTime(INT_MAX), finishDiscoveryTime(INT_MAX){}

        int getValue(){return value;}
        Node* getPredecessor(){return predecessor;}
        Color getColor(){return color;}
        vector<Node*>& getAdj(){return adj;}
        int getDiscovery(){return discoveryTime;}
        int getFinishDiscovery(){return finishDiscoveryTime;}
        int getDistance(){return distance;}

        void setPredecessor(Node* node){ predecessor = node;}
        void setColor(Color c){color = c;}
        void setAdj(Node* adj_node){adj.push_back(adj_node);}
        void setDiscoveryTime(int disc){discoveryTime = disc;}
        void setFinishDiscoveryTime(int finish){finishDiscoveryTime = finish;}
        void setDistance(int dist){distance = dist;}

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
};

class Graph{

    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E, time;
        stack<Node*>L;


        void DFS_VISIT(Node* n){

            n->setColor(gray);
            time++;
            n->setDiscoveryTime(time);

            for(Node* adj : n->getAdj()){
                if(adj->getColor() == white){
                    adj->setPredecessor(n);
                    DFS_VISIT(adj);
                }
            }

            n->setColor(black);
            time++;
            n->setFinishDiscoveryTime(time);
            L.push(n);
        }

        bool isSafe(Node* v, vector<Node*>& path, int pos){
            Node* lastNode = path[pos - 1];
            bool isAdj = false;

            for(Node* adj_node : lastNode->getAdj()){
                if(adj_node == v){
                    isAdj = true;
                    break;
                }
            }

            if(!isAdj)
                return false;

            for(int i = 0; i < pos; i++){
                if(path[i] == v){
                    return false;
                }
            }

            return true;
        }

        bool hamiltonianCycle(vector<Node*>& path, int pos){
            if(pos == V){
                Node* lastNode = getNode(pos -1);
                
                for(Node* adjNode : lastNode->getAdj()){
                    if(adjNode == path[0])
                        return true;
                }
                return false;
            }

            for(auto& v : nodes){
                if(isSafe(v, path, pos)){
                    path[pos] = v;

                    if(hamiltonianCycle(path, pos+1))
                        return true;
                    
                    path[pos] = nullptr;
                }
            }

            return false;
        }

        void initializeSingleSource(Node* s){
            for(auto& u : nodes){
                u->setDistance(INT_MAX);
                u->setPredecessor(nullptr);
            }
            s->setDistance(0);
            s->setPredecessor(nullptr);
        }

        void relax(Edge* edge){
            if(edge->getDest()->getDistance() > edge->getSrc()->getDistance() + edge->getWeight()){
                edge->getDest()->setDistance(edge->getSrc()->getDistance() + edge->getWeight());
                edge->getDest()->setPredecessor(edge->getSrc());
            }
        }

        struct compare{
            bool operator()(Node* u, Node* v){
                return u->getDistance() > v->getDistance();
            }
        };

    public:

        Graph(int v, int e) : V(v), E(e){}

        void addNode(Node* node){
            nodes.push_back(node);

            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        void addEdge(Node* u, Node* v, int w){

            edges.push_back(new Edge(u,v,w));
            u->setAdj(v);

            if(edges.size() > E){
                E = edges.size();
            }
        }

        Node* getNode(int val){

            for(auto& node : nodes){
                if(node->getValue() == val )
                    return node;
            }
            return nullptr;
        }

        Edge* getEdge(Node* u, Node* v){

            for(auto& edge : edges){
                if(edge->getSrc() == u && edge->getDest() == v)
                    return edge;
            }
            return nullptr;
        }

        void DFS(){

            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
            }

            time++;

            for(auto& node : nodes){
                if(node->getColor() == white){
                    DFS_VISIT(node);
                }
            }
        }

        void topologicalPrint(ofstream& out){
            while(!L.empty()){
                Node* node = L.top();
                L.pop();
                out << node->getValue() << endl;
            }
            
        }

        bool findHamiltonianCycle(int  pos){

            vector<Node*> path(V, nullptr);
            path[0] = getNode(pos);

            if(hamiltonianCycle(path, pos+1)){
                cout << "\n Ciclo Hamiltoniano trovato: ";

                for(int i =0; i < V; i++){
                    cout<<path[i]->getValue()<<endl;
                }
                cout<<path[0]->getValue()<<endl;
                return true;
            }
            else{
                cout << "\nNon esiste un ciclo Hamiltoniano!" << endl;
                return false;
            }
        }

        void bellmanFord(Node* s, Node* d){
            initializeSingleSource(s);

            for(int i = 0; i < V; i++){
                for(auto& edge : edges){
                    relax(edge);
                }
            }

            vector<int> path;
            Node* n = d;

            while(n != nullptr){
                path.push_back(n->getValue());
                n = n->getPredecessor();
            }

            cout << "\n Distanza tra il nodo" << s->getValue() << " e il nodo " << d->getValue() << ": "<< d->getDistance();
            
            cout << "\n Cammino di peso minimo: ";
            for(int i = path.size()-1; i >= 0; i--){
                cout << path[i]<< " ";
            }
            cout<<endl<<endl;
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

                for (Node* v : u->getAdj()) {
                    Edge* edge = getEdge(u,v);

                    if (edge != nullptr) {
                        relax(edge);

                        if (visited.find(v) == visited.end())
                            minPQ.push(v);
                    }
                }
            }

            cout << "\nDistanze minime dal nodo " << s->getValue() << ":" << endl;
            for (auto& u : nodes)
                cout << "Node: " << u->getValue() << ", distance: " << u->getDistance() << endl;
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