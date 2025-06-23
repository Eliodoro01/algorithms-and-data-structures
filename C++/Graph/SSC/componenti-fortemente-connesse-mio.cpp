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

enum Color{white, black, gray};

class Node{

    private:
        int value;
        Node* predecessor;
        vector<Node*> adj;
        Color color;
        int discoveryTime;
        int finishDiscovery;
        int distance;

    public:

        Node(int value) : value(value), predecessor(nullptr), adj(nullptr), color(white), discoveryTime(INT_MAX), finishDiscovery(INT_MAX), distance(INT_MAX){}

        int getValue(){return value;}
        Node* getPredecessor(){return predecessor;}
        Color getColor(){return color;}
        vector<Node*>& getAdj(){return adj;}
        int getDiscovery(){return discoveryTime;}
        int getFinishDiscovery(){return finishDiscovery;}
        int getDistance(){return distance;}

        void setPredecessor(Node* node){ predecessor = node;}
        void setColor(Color c){color = c;}
        void setAdj(Node* adj_node){adj.push_back(adj_node);}
        void setDiscoveryTime(int disc){discoveryTime = disc;}
        void setFinishDiscoveryTime(int finish){finishDiscovery = finish;}
        void setDistance(int dist){distance = dist;}

};

class Edge{

    private:
        Node* src;
        Node* dest;
        int weight;

    public:
        Edge(Node* u, Node* v, int w): src(u), dest(v), weight(w){}

        Node* getSrc(){return src;}
        Node* getDest(){return dest;}
        int getWeight(){return weight;}
};

class Graph{

    private:
        vector<Node*>nodes;
        vector<Edge*>edges;
        int V, E, time;
        stack<Node*> L;

        void DFS_VISIT(Node* node){

            node->setColor(gray);
            time++;
            node->setDiscoveryTime(time);

            for(Node* adj : node->getAdj()){
                if(adj->getColor() == white){
                    adj->setPredecessor(node);
                    DFS_VISIT(adj);
                }
            }

            node->setColor(black);
            time++;
            node->setFinishDiscoveryTime(time);
            L.push(node);

        }

        void initializeSingleSource(Node* s){

            for(auto& node : nodes ){
                node->setDistance(INT_MAX);
                node->setPredecessor(nullptr);
            }

            s->setDistance(INT_MAX);
            s->setPredecessor(nullptr);
        }

        void relax(Edge* edge){
            if(edge->getDest()->getDistance() > edge->getSrc()->getDistance() + edge->getWeight()){
                edge->getDest()->setDistance(edge->getSrc()->getDistance() + edge->getWeight());
                edge->getDest()->setPredecessor(edge->getSrc());
            }
        }

    public:
        Graph(int v, int e) : V(v), E(e){}
        
        void addNode(Node* node){
            nodes.push_back(node);

            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        Node* getNode( int key){
            
            for(auto& node : nodes){
                if(node->getValue() == key){
                    return node;
                }
            }
            return nullptr;
        }

        void addEdge(Node* src, Node* dest, int w){
            edges.push_back(new Edge(src, dest, w));

            if(edges.size() > E){
                E = edges.size();
            }
        }

        Edge* getEdge(Node* src, Node* dest){

            for(auto& edge : edges){
                if(edge->getSrc() == src &&edge->getDest() == dest)
                    return edge;
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

        void topologicalPrint(ofstream& out){
            while(!L.empty()){
                Node* node = L.top();
                L.pop();
                out << node->getValue() << endl;
            }
        }

        void bellmanFord(Node* s, Node* d){

        }


};