#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node* predecessor;
        Color color;
        int value;
        vector<Node*> adj;
        int startVisit;
        int finishVisit;

    public:
        Node(int v) :value(v), predecessor(nullptr), color(white), startVisit(INT_MAX), finishVisit(INT_MAX){}

        int getValue(){return value;}
        Color getColor(){return color;}
        vector<Node*> getAdj(){return adj;}
        int getStartVisit(){return startVisit;}
        int getFinishVisit(){return finishVisit;}
        Node* getPredecessor(){return predecessor;}

        void setPredecessor(Node* pred){predecessor = pred;}
        void setStartVisit(int d){startVisit = d;}
        void setFinishVisit(int f){finishVisit = f;}
        void setColor(Color c){color = c;}
        void setAdj(Node* a){adj.push_back(a);}

};

class Edge{

    private:
        Node* src;
        Node* dest;
        int weight;
        string type;

    public:
        Edge(Node* u, Node* v, int w) : src(u), dest(v), weight(w), type(""){}

        int getWeight(){return weight;}
        Node* getSrc(){return src;}
        Node* getDest(){return dest;}
        string getType(){return type;}

        void setSrc(Node* u){src = u;}
        void setDest(Node* v){dest = v;}
        void setType(string t){type = t;}
};


class Graph{

    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E, weights, u, v, w, time, cycleCount;
        vector<Node*> path;

        void load(ifstream& in){
            string totalTokens;
            getline(in, totalTokens);
            if(totalTokens.front() == '<')
                totalTokens = totalTokens.substr(1);
            if(totalTokens.back() == '>')
                totalTokens.pop_back();
            for(char& c : totalTokens){
                if(c == ',')
                    c = ' ';
            }

            istringstream stream(totalTokens);
            stream >> V >> E;

            for(int i = 0; i < V; i++){
                addNode(i);
            }

           while(getline(in, totalTokens)){
                if(totalTokens.front() == '<')
                    totalTokens = totalTokens.substr(1);
                if(totalTokens.back() == '>')
                    totalTokens.pop_back();
                for(char& c : totalTokens){
                    if(c == ',')
                        c = ' ';
                }

                istringstream stream(totalTokens);

                while(stream >> u >> v >> w){
                    Node* src = getNode(u);
                    Node* dest = getNode(v);
                    if(src != nullptr && dest != nullptr){
                        addEdge(src, dest, w);
                    }
                }
                    
            }
        }

        void dfsVisit(Node* node){

            node->setColor(gray);
            time = time + 1;
            node->setStartVisit(time);
            path.push_back(node);

            for(auto& adj : node->getAdj()){
                Edge* edge = getEdge(node, adj);
                if(adj->getColor() == white){
                    edge->setType("dell'albero");
                    adj->setPredecessor(node);
                    dfsVisit(adj);
                }
                else if(adj->getColor() == gray){
                    cout << "Ciclo trovato" << endl;
                    edge->setType("all'indietro");

                    int startIndex = -1;

                    for(int i = 0; i < path.size(); i++){
                        if(path[i] == adj){
                            startIndex = i;
                            break;
                        }
                    }

                    if(startIndex != -1){
                        for(int i = startIndex; i < path.size(); i++){
                            cout << path[i]->getValue() << " ";
                        }
                        cout << adj->getValue()<<endl;
                        cycleCount++;
                    }
                }

                else if(adj->getColor() == black && node->getStartVisit() > node->getFinishVisit())
                    edge->setType("trasversale");
                else if(adj->getColor() == black && node->getStartVisit() < node->getFinishVisit())
                    edge->setType("in avanti");
            }
            node->setColor(black);
            time = time+1;
            node->setFinishVisit(time);
            path.pop_back();
        }

        

    public:
        Graph(ifstream& in) : cycleCount(0){
            load(in);
        }

        int getCycleCount(){return cycleCount;}

        Node* getNode(int key){
            for(auto& node : nodes){
                if(node->getValue() == key)
                    return node;
            }
           cout << "nodo non trovato"<<endl;
        }

        void addEdge(Node* src, Node* dest, int w){

            edges.push_back(new Edge(src, dest, w));
            src->setAdj(dest);
            if(edges.size() > E){
                E = edges.size();
            }
        }

        void addNode(int val){
            nodes.push_back(new Node(val));
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
            cout<<"Arco non trovato"<<endl;
        }

        void dfs(){
            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
            }

            for(auto& node : nodes){
                if(node->getColor() == white){
                    dfsVisit(node);
                }
            }
        }


        

        void printEdges(){
            for(auto& edge : edges){
                cout<< "Src: " << edge->getSrc()->getValue() << " Dest: "<< edge->getDest()->getValue() << " Type: "<< edge->getType() << endl; 
            }
        }


};


int main(){

    ifstream in("input.txt");

    Graph graph(in);

    graph.dfs();
    cout << endl << endl;
    graph.printEdges();
    cout<< "Numero di cicli: " << graph.getCycleCount() << endl;

}

/*
<4,5>
<0,1,1>
<1,2,1>
<2,3,1>
<3,1,1>   // forma un ciclo
<0,2,1>
*/