#include <stdio.h>
#include <iostream>
#include <fstream>
#include<vector>
#include <climits>

using namespace std;

enum Color{white, gray, black};

class Node{

    private:
        Node* predecessor;
        int value;
        vector<Node*> adj;
        Color color;
        int discoveryTime;
        int finishTime;
    
    public:
        Node(int v) : value(v), predecessor(nullptr), color(white), startVisit(INT_MAX), finishVisit(INT_MAX){}

        void setPredecessor(Node* node){ predecessor = node;}
        void setDiscoveryTime(int d){discoveryTime = d;}
        void setFinishTime(int t){finishTime = t;}
        void setColor(Color c){color = c;}
        void setAdj(vector<Node*> adj_node){adj.push_back(adj);}

}