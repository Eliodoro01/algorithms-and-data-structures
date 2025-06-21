#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <climits>


using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node* predecessor;
        int key;
        Color color;
        vector<Node*> adj;
        int startVisitTime;
        int finishVisitTime;
    
    public:
        Node(int value) : key(value), predecessor(nullptr), color(white), startVisitTime(INT_MAX), finishVisitTime(INT_MAX){}

        Node* getPredecessor(){return predecessor;}
        int getKey(){return key;}
        vector<Node*> getAdj(){return adj;}
        Color getColor(){return color;}
        int getStartVisit(){return startVisitTime;}
        int getFinishVisit(){return finishVisitTime;}

        void setPredecessor(Node* node){predecessor = node;}
        void setColor(Color c){color = c;}
        void setAdj(Node* adj_node){adj.push_back(adj_node);}
        void setStartVisit(int d){startVisitTime = d;}
        void setFinishVisit(int f){finishVisitTime = f;}
};

class Edge{

    private:
        Node* src;
        Node* dest;
        int weight;
        string type;

    public:

        Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w){}

        Node* getDest(){return dest;}
        Node* getSrc(){return src;}
        int getWeight(){return weight;}
        string getType(){return type;}

        void setSrc(Node* u){src = u;}
        void setDest(Node* v){dest = v;}
        void setWeight(int w){weight = w;}
        void setType(string t){type = t;}

};


class Graph{

    private: 
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E, time, cycleCount;

        void DFS_VISIT(Node * node, vector<Node*> path){

            node->setColor(gray);
            time++;
            node->setStartVisit(time);
            path.push_back(node);

            for(Node* adj : node->getAdj()){
                Edge* edge = getEdge(node, adj);

                if(adj->getColor() == white){
                    edge->setType("dell'albero");
                    adj->setPredecessor(node);

                    DFS_VISIT(adj, path);
                }
                else if(adj->getColor() == gray){
                    edge->setType("all'indietro");

                    cout<<"ciclo trovato"<<endl;
                    int startIndex = -1;
                    for(int i = 0; i < path.size(); i++){
                        if(path[i] == adj){
                            startIndex = i;
                            break;
                        }
                    }
                    if(startIndex != -1){
                        for(int i = startIndex; i < path.size(); i++){
                            cout<< path[i]->getKey() << " ";
                        }
                        cout<< adj->getKey() << endl;
                        cycleCount++;
                    }
                }
                else if(adj->getColor() == black && node->getStartVisit() > adj->getStartVisit())
                    edge->setType("trasversale");
                else if(adj->getColor() == black && node->getStartVisit() < adj->getStartVisit())
                    edge->setType("in avanti");
            }

            node->setColor(black);
            time++;
            node->setFinishVisit(time);
            path.pop_back();
        }

    public:

        Graph(int v, int e) : V(v), E(e), time(0), cycleCount(0){}

        int getCycleCount(){
            return cycleCount;
        }

        Node* getNode(int key){
            for(auto& node : nodes){
                if(node->getKey() == key){
                    return node;
                }
            }
            return nullptr;
        }

        void addNode(Node* node){
            nodes.push_back(node);
            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        Edge* getEdge(Node* src, Node* dest){

            for(auto& edge : edges){
                if(edge->getSrc() == src && edge->getDest() == dest){
                    return edge;
                }
            }
            return nullptr;
        }

        void addEdge(Node* src, Node* dest, int weight){
            edges.push_back(new Edge(src, dest, weight));
            
            src->setAdj(dest);
            if(edges.size() > E){
                E = edges.size();
            }
        }

        void DFS(){

            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
            }

            vector<Node*>path;
            cycleCount =0;

            for(auto& node : nodes){
                if(node->getColor() == white){
                    DFS_VISIT(node, path);
                }
            }
        }

        void print(ofstream& out){
            for(auto& node : nodes){
                out<< node->getKey() << endl;
            }
        }

        void printEdges(){
            for(auto& edge : edges){
                cout << " L'arco(" << edge->getSrc()->getKey() << "," << edge->getDest()->getKey() << ") e' un arco " << edge->getType()<<endl; 
            }
        }
    
};


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int V, E;

    in >> V >> E;

    Graph gp(V,E);

    for(int i = 0; i < V; i++){
        gp.addNode(new Node(i));
    }

    for(int i = 0; i < E; i++){
        int u,v, w;

        in >> u >> v >> w;

        Node* src = gp.getNode(u);
        Node* dest = gp.getNode(v);
        
        if(src != nullptr && dest != nullptr)
            gp.addEdge(src, dest, w);
        else   
            cout << "Errore: nodo " << u << " o " << v << " non esistente!" << endl;
    }

    gp.DFS();
    gp.print(out);
    gp.printEdges();

    in.close();
    out.close();

    cout << " numero di cicli trovati: " << gp.getCycleCount() << endl;
    

}