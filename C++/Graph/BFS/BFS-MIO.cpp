#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node*predecessor;
        vector<Node*> adj;
        Color color;
        int value;
        int distance;

    public:

        Node(int key) : value(key), predecessor(nullptr), color(white), distance(INT_MAX){}

        int getValue(){return value;}
        int getDistance(){return distance;}
        Node* getPredecessor(){return predecessor;}
        vector<Node*> getAdj(){return adj;}
        Color getColor(){return color;}

        void setColor(Color c){c = color;}
        void setPredecessor(Node* node){predecessor = node;}
        void setAdj(Node* node){adj.push_back(node);}
        void setDistance(int d){distance = d;}
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
        void setWeight(int w){weight = w;}

};


class Graph{

    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E;

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

        Node* getNode(int value){
            for(auto& node : nodes){
                if(node->getValue() == value){
                    return node;
                }
            }
            return nullptr;
        }

        void addEdge(Node* src, Node* dest, int weight){

            edges.push_back(new Edge(src, dest, weight));
            src->setAdj(dest);
            dest->setAdj(src);

            if(edges.size() > E){
                E = edges.size();
            }
        }

        Edge* getEdge(Node* src, Node* dest){
            for(auto& edge : edges){
                if(edge->getSrc() == src && edge->getDest() == dest)
                    return edge;
            }
            return nullptr;
        }


        void BFS(Node* source, ofstream& out){

            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
                node->setDistance(INT_MAX);
            }

            source->setColor(gray);
            source->setDistance(0);

            queue<Node*> q;
            q.push(source);

            while(!q.empty()){

                Node* node = q.front();
                q.pop();

                for(Node* adj : node->getAdj()){
                    if(adj->getColor() == white){
                        adj->setPredecessor(node);
                        adj->setColor(gray);
                        adj->setDistance(node->getDistance() + 1);

                        q.push(adj);
                    }
                }

                node->setColor(black);
            }

            for(auto& node : nodes){
                if(node->getPredecessor() == nullptr)
                    out << "Node: " << node->getValue() << " -> (predecessor: NULL, distance: " << node->getDistance() << ")"<<endl;
                else
                    out << "Node: "<< node->getValue() << " -> (predecessor: " << node->getPredecessor() << " distance: " << node->getDistance() << ")"<<endl;
            }

        }

        void prim(Node* s){
            for(auto& node : nodes){
                node->setPredecessor(nullptr);
                node->setDistance(INT_MAX);
            }

            s->setDistance(0);

            vector<bool> inMST(V, false);
            priority_queue<Node*, vector<Node*>, compare> minPQ;
            minPQ.push(s);

            while(!minPQ.empty()){
                Node* node = minPQ.top();
                minPQ.pop();
                inMST[node->getValue()] = true;

                for(auto& adj : node->getAdj()){
                    Edge* edge = getEdge(node, adj);
                    if(!inMST[adj->getValue()] && edge->getWeight() < adj->getDistance() ){
                        adj->setDistance(edge->getWeight());
                        adj->setPredecessor(node);
                        minPQ.push(adj);
                    }
                }
            }
        }

        void printMST(){
            cout << " Minimum spanning tree:"<<endl;

            for(auto& node : nodes){
                if(node->getPredecessor() == nullptr)
                    cout << "Il nodo con valore: " << node->getValue() << " -> (predecessor: NULL, distance: " << node->getDistance() << ")"<<endl;
                else
                    cout << "Il nodeo con valore: " << node->getValue() << "-> (predecessor: " << node->getPredecessor() << " distance: " << node->getDistance() <<")"<<endl;
            }
        }

};


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");
    int V, E;

    in >> V >> E;

    Graph graph(V,E);
    for(int i = 0; i < V; i++){
        graph.addNode(new Node(i));
    }

    for(int i = 0; i < V; i++){
        int u, v, w;

        in >> u >> v>> w;

        Node* src = graph.getNode(u);
        Node* dest = graph.getNode(v);

        if(src != nullptr && dest != nullptr)
            graph.addEdge(src, dest, w);
        else
            cout<< " Non e' stato possibile aggiungere l'arco poiche' il nodo "<< u << "e/o il nodo:" << v << "sono nullptr"<<endl;
    }
}