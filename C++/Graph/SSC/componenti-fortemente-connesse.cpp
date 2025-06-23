#include <iostream>             // Per input/output su console
#include <vector>               // Per usare vettori dinamici
#include <stack>                // Per usare lo stack (LIFO)
#include <fstream>              // Per leggere/scrivere su file

using namespace std;

class Graph {
    int V;                          // Numero di vertici
    vector<vector<int>> adj;        // Lista di adiacenza per il grafo originale
    vector<vector<int>> adjRev;     // Lista di adiacenza per il grafo trasposto

public:
    Graph(int V) {
        this->V = V;                // Imposta numero di vertici
        adj.resize(V);              // Inizializza la lista di adiacenza
        adjRev.resize(V);           // Inizializza il grafo trasposto
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);       // Aggiunge arco u → v al grafo originale
        adjRev[v].push_back(u);    // Aggiunge arco v → u al grafo trasposto
    }

    void dfs(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;              // Segna il nodo come visitato
        for (int u : adj[v]) {          // Visita tutti i vicini di v nel grafo originale
            if (!visited[u])
                dfs(u, visited, Stack); // DFS ricorsiva su u
        }
        Stack.push(v);             // Inserisce v nello stack dopo aver visitato i discendenti
    }

    void dfsReverse(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;             // Segna v come visitato
        component.push_back(v);        // Aggiunge v alla componente corrente
        for (int u : adjRev[v]) {      // Visita i vicini nel grafo trasposto
            if (!visited[u])
                dfsReverse(u, visited, component); // DFS ricorsiva su u
        }
    }

    void printSCCs(ofstream& out) {
        stack<int> Stack;                          // Stack per salvare l’ordine di completamento
        vector<bool> visited(V, false);            // Vettore di nodi visitati

        for (int i = 0; i < V; i++) {              // Prima DFS: riempi lo stack
            if (!visited[i]) 
                dfs(i, visited, Stack);
        }

        fill(visited.begin(), visited.end(), false); // Reset del vettore visited

        while (!Stack.empty()) {                   // Seconda DFS: sul grafo trasposto
            int v = Stack.top(); Stack.pop();      // Prende il prossimo nodo dallo stack

            if (!visited[v]) {
                vector<int> component;             // Lista per salvare una SCC
                dfsReverse(v, visited, component); // DFS sul grafo trasposto

                for (int node : component)         // Scrive la componente sul file
                    out << node << " ";
                out << "\n";
            }
        }
    }
};

int main() {
    ifstream in("input.txt");                          // Apre il file in input
    if (!in) {
        cerr << "Errore apertura file" << endl;
        return 1;                                      // Se fallisce, esce con errore
    }

    int N, M;
    in >> N >> M;                                      // Legge numero di nodi e archi

    Graph g(N);                                        // Crea un grafo con N nodi

    for (int i = 0; i < M; i++) {
        int u, v;
        in >> u >> v;                                  // Legge ogni arco
        g.addEdge(u, v);                               // Aggiunge l’arco al grafo
    }
    in.close();                                        // Chiude il file in input

    ofstream out("output.txt");                    // Apre file in scrittura
    if (!out) {
        cerr << "Errore apertura file " << endl;
        return 1;                                      // Se fallisce, esce con errore
    }

    g.printSCCs(out);                                  // Stampa le SCC su file
    out.close();                                       // Chiude il file in output

    cout << "Componenti fortemente connesse scritte " << endl;

    return 0;
}
