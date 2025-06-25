#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class MaxHeap{

    private:
        vector<int> heap; // Vettore che rappresenta l'heap binario

        int left(int i){
            return 2*i + 1; // Indice del figlio sinistro di i
        }

        int right(int i){
            return 2*i + 2; // Indice del figlio destro di i
        }

        int parent(int i){
            return (i-1) / 2; // Indice del genitore del nodo i
        }

        void maxHeapify(int i, int heapSize){
            int l = left(i);        // Calcolo indice del figlio sinistro
            int r = right(i);       // Calcolo indice del figlio destro
            int max = i;            // Inizialmente supponiamo che il massimo sia il nodo corrente

            if(l < heapSize && heap[l] > heap[max])
                max = l;            // Se il figlio sinistro esiste ed è maggiore, aggiorna max
            if(r < heapSize && heap[r] > heap[max])
                max = r;            // Se il figlio destro esiste ed è maggiore, aggiorna max
            
            if(max != i){
                swap(heap[i], heap[max]);     // Se un figlio è maggiore, scambialo con il nodo corrente
                maxHeapify(max, heapSize);    // Richiama ricorsivamente su max per mantenere proprietà heap
            }
        }

    public:
        MaxHeap(const vector<int>& data){
            heap = data;           // Inizializza il vettore heap con i dati passati
            buildMaxHeap();        // Costruisce l'heap a partire dai dati non ordinati
        }

        void buildMaxHeap(){
            int heapSize = heap.size();

            for(int i = (heapSize/2) - 1; i >= 0; i--){
                maxHeapify(i, heapSize);    // Applica maxHeapify ai nodi non foglia (da metà verso l'alto)
            } 
        }

        void heapSort(){
            int heapSize = heap.size();      // Salva dimensione iniziale dell'heap

            buildMaxHeap();                  // Ricostruisce l'heap (precauzione per sicurezza)

            for(int i = heapSize - 1; i >= 1; i--){
                swap(heap[0], heap[i]);      // Sposta il massimo (radice) in fondo all'array
                heapSize--;                  // Riduce l'heap escludendo l'ultimo elemento ordinato
                maxHeapify(0, heapSize);     // Ripristina proprietà heap sulla nuova radice
            }
        }

        void printHeap() const{
            for(int val: heap){
                cout << val << " ";          // Stampa tutti gli elementi dell'heap
            }
            cout << endl;
        }

};


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<int> data;
    int x;

   
    while(in >> x)
        data.push_back(x);
    
    MaxHeap heap(data);
    
    heap.printHeap();

    heap.heapSort();

    cout << "Heap dopo il sort"<<endl;
    heap.printHeap();

    return 0;

}