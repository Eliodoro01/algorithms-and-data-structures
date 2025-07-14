#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node* predecessor;
        vector<Node*> adj;
        Color color;
        int value;
        int distance;
        int startVisit;
        int endVisit;

    public:
        Node(int v) : value(v), predecessor(nullptr), color(white), distance(INT_MAX){}

        Node* getPredecessor(){return predecessor;}
        vector<Node*> getAdj(){return adj;}
        Color getColor(){return color;}
        int getValue(){return value;}
        int getDistance(){return distance;}
        int getStartVisit(){return startVisit;}
        int getEndVisit(){return endVisit;}

        void setPredecessor(Node* p){predecessor = p;}
        void setAdj(Node* a){adj.push_back(a);}
        void setDistance(int d){distance = d;}
        void setColor(Color c){color = c;}
        void setStartVisit(int d){startVisit = d;}
        void setEndVisit(int f){endVisit = f;}

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
        
        Node* getSrc(){return src;}
        Node* getDest(){return dest;}
        int getWeight(){return weight;}
        string getType(){return type;}
};


class Graph{

    private:
        vector<Node*>nodes;
        vector<Edge*> edges;
        int V, E, cycleCount, time = 0;
        stack<Node*> S;
        stack<Node*> topo;
        vector<Node*> path;
        vector<bool>visited;
        stack<Node*>L;

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
            int u, v, w;
            istringstream stream(totalTokens);
            stream >> V >> E;

            for(int i = 0; i < V; i++){
                addNode(i);
            }

            while (getline(in, totalTokens)){
                if(totalTokens.front() == '<')
                totalTokens = totalTokens.substr(1);
                if(totalTokens.back() == '>')
                    totalTokens.pop_back();
                for(char& c : totalTokens){
                    if(c == ',')
                        c = ' ';
                }

                istringstream stream(totalTokens);
                stream >> u >> v >> w;
                Node* src = getNode(u);
                Node* dest = getNode(v);
                addEdge(src, dest, w);

                stream.clear();
                stream.str("");
            }
            
        }

        void addNode(int key){
            nodes.push_back(new Node(key));

            if(nodes.size() > V){
                V = nodes.size();
            }
        }

        void addEdge(Node* src, Node* dest, int w){
            edges.push_back(new Edge(src, dest, w));
            src->setAdj(dest);

            if(edges.size() > E){
                E = edges.size();
            }
        }

        Edge* getEdge(Node* src, Node* dest){
            for(auto& edge : edges){
                if(edge->getSrc() == src && edge->getDest() == dest){
                    return edge;
                }
            }
            cout << "Edge non trovato" << endl;
            return nullptr;
        }

        void dfsVisit(Node* node){
            node->setColor(gray);
            ++time;
            node->setStartVisit(time);
            path.push_back(node);

            for(auto& adj : node->getAdj()){
                Edge* edge = getEdge(node, adj);

                if(adj->getColor() == white){
                    edge->setType("Dell'albero");
                    adj->setPredecessor(node);

                    dfsVisit(adj);
                }

                else if(adj->getColor() == gray){
                    cout << "Ciclo trovato" << endl;
                    edge->setType("All'indietro");

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
                        cout << adj->getValue() << " " << endl;
                        cycleCount++;
                    }

                }
                else if(adj->getColor() == black && node->getStartVisit() > adj->getStartVisit())
                    edge->setType("Trasversale");
                else if(adj->getColor() == black && node->getStartVisit() < adj->getStartVisit())
                    edge->setType("In avanti");
            }
            node->setColor(black);
            ++time;
            node->setEndVisit(time);
            topo.push(node);
        }

        void fillOrder(Node* node){
            node->setColor(gray);
            for(auto* adj : node->getAdj()){
                if(adj->getColor() == white){
                    fillOrder(adj);
                }
            }
            L.push(node);
        }

        Graph* getTranspose(){

            Graph* gt = new Graph;

            for(int i = 0; i < V; i++){
                gt->addNode(i);
            }

            for(auto& edge : edges){
                Node* newSrc = gt->getNode(edge->getDest()->getValue());
                Node* newDest = gt->getNode(edge->getSrc()->getValue());
                gt->addEdge(newSrc, newDest, edge->getWeight());
            }

            return gt;
        }

        void dfsUtil(Node* node){

            visited[node->getValue()] = true;
            cout << node->getValue() << " ";
            for(Node* adj : node->getAdj()){
                if(!visited[adj->getValue()]){
                    dfsUtil(adj);
                }
            }
        }

    public:
        Graph(ifstream& in){
            load(in);
        }

        Graph(){}

        Node* getNode(int key){
            for(auto& node : nodes){
                if(node->getValue() == key){
                    return node;
                }
            }
            cout << "Nodo non trovato" << endl;
            return nullptr;
        }

        void bfs(Node* source){

            for(auto& node : nodes){
                node->setColor(white);
                node->setDistance(INT_MAX);
                node->setPredecessor(nullptr);
            }

            source->setDistance(0);
            source->setColor(gray);

            queue<Node*> q;
            q.push(source);

            while(!q.empty()){
                Node* node = q.front();
                q.pop();

                for(auto& adj : node->getAdj()){
                    if(adj->getColor() == white){
                        adj->setPredecessor(node);
                        adj->setDistance(node->getDistance() + 1);
                        adj->setColor(gray);

                        q.push(adj);
                    }
                }
                node->setColor(black);
            }
        
        }

        void dfs(){

            for(auto& node : nodes){
                node->setColor(white);
                node->setPredecessor(nullptr);
            }

            for(auto& node: nodes){
                if(node->getColor() == white){
                    dfsVisit(node);
                }
            }
        }

        void print(){
            for(auto& node : nodes){
                if(node->getPredecessor() != nullptr)
                    cout << "Node->"<< node->getValue() << " Predecessor->" << node->getPredecessor()->getValue() << " Distance->" << node->getDistance() << endl; 
                else
                    cout << "Node->"<< node->getValue() << " Predecessor-> nullptr"  << " Distance->" << node->getDistance() << endl;
            }
        }

        void printTopo(){
            cout << "Stampa topologica: " << endl;
            while (!topo.empty()){
                Node* node = topo.top();
                topo.pop();
                cout << node->getValue() << " ";
            }
            
        }

        void printSCC(){

            for(auto& node : nodes){
                node->setColor(white);
            }

            for(auto& node : nodes){
                if(node->getColor() == white){
                    fillOrder(node);
                }
            }

            Graph* gt = getTranspose();
            visited.assign(V, false);

            cout <<"Componenti fortemente connesse:" << endl;

            while(!L.empty()){
                Node* node = L.top();
                L.pop();
                if(!visited[node->getValue()]){
                    dfsUtil(gt->getNode(node->getValue()));
                    cout << endl;
                }
            }

            delete gt;
        }

        void printEdges(){
            for(auto& edge : edges){
                if(edge->getSrc() != nullptr && edge->getDest() != nullptr)
                    cout << "Src->" << edge->getSrc()->getValue() << " Dest->" << edge->getDest()->getValue() << " Type->" << edge->getType() << endl;
                else
                    cout << "Nullptr" << endl;
            }
        }

};


int main(){


    ifstream in("input.txt");

    Graph gp(in);

    Node* x = gp.getNode(0);

    gp.bfs(x);
    gp.print();

    gp.dfs();
    gp.printEdges();

    gp.printSCC();

}

/*<6,7>
<0,1,1>
<1,2,1>
<2,0,1>
<3,4,1>
<4,5,1>
<5,3,1>
<2,3,1>*/