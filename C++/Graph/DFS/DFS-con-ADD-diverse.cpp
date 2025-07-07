#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <sstream>

using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node* predecessor;
        int value;
        vector<Node*>adj;
        int startVisit;
        int endVisit;
        Color color;
    
    public:
        Node(int v): value(v), predecessor(nullptr), startVisit(INT_MAX), endVisit(INT_MAX), color(white){}

        void setColor(Color c){color =c;}
        void setStartVisit(int start){startVisit = start;}
        void setEndVisit(int end){endVisit = end;}
        void setPredecessor(Node* pre){predecessor = pre;}
        void setAdj(Node* a){adj.push_back(a);}

        int getValue(){return value;}
        Color getColor(){return color;}
        Node* getPredecessor(){return predecessor;}
        vector<Node*> getAdj(){return adj;}
        int getStartVisit(){return startVisit;}
        int getEndVisit(){return endVisit;}
};



class Edge{

    private:
        Node* src;
        Node* dest;
        int weight;
        string type;

    public:
        Edge(Node* u, Node* v, int w): src(u), dest(v), weight(w), type(""){}

        void setSrc(Node* u){src = u;}
        void setDest(Node* v){dest = v;}
        void setType(string t){type = t;}

        int getWeight(){return weight;}
        Node* getSrc(){return src;}
        Node* getDest(){return dest;}
        string getType(){return type;}

};

class Graph{

    private:
        vector<Node*> nodes;
        vector<Edge*> edges;
        int V, E, u, v, w, type;
        vector<Node*> path;
        int cycleCount = 0, time = 0;

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
                addNode(new Node(i));
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
                while (stream >> u >> v>> w)
                {
                    Node* src = getNode(u);
                    Node* dest = getNode(v);
                    addEdge(new Edge(src, dest, w));
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
                    edge->setType(" Arco dell'albero ");
                    adj->setPredecessor(node);
                    dfsVisit(adj);
                }

                else if(adj->getColor() == gray){
                    cout << " ciclo trovato"<<endl;
                    edge->setType(" Arco all'indietro ");
                    int startIndex = -1;

                    for(int i = 0; i < path.size(); i++){
                        if(path[i] == adj){
                            startIndex = i;
                            break;
                        }
                    }

                    if(startIndex != -1){
                        for(int i = startIndex; i < path.size(); i++){
                            cout<<path[i]->getValue() << " ";
                        }
                        cout << adj->getValue()<<endl;
                        cycleCount++;
                    }
                }

                else if(adj->getColor() == black && node->getStartVisit() > adj->getStartVisit())
                    edge->setType(" Arco trasversale ");
                else if(adj->getColor() == black && node->getStartVisit() < adj->getStartVisit())
                    edge->setType(" Arco in avati ");
            }

            node->setColor(black);
            time = time+ 1;
            node->setEndVisit(time);
            path.pop_back();

        }


    public:
        Graph(ifstream& in){
            load(in);
        }

        int getCycleCount(){return cycleCount;}

        void addNode(Node* node){
            if(node != nullptr){
                nodes.push_back(node);
            }

            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        void addEdge(Edge* edge){

            if(edge != nullptr){
                edges.push_back(edge);
                edge->getSrc()->setAdj(edge->getDest()); 
            }

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

        Edge* getEdge(Node* src, Node* dest){

            for(auto& edge : edges){
                if(edge->getSrc() == src && edge->getDest() == dest){
                    return edge;
                }
            }
            return nullptr;
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