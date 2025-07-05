#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;


class MaxHeap{

    private:
        vector<int> heap;
        int heapSize;

        int getLeft(int i){return i * 2 + 1;}
        int getRight(int i){return i * 2 + 2;}
        int getParent(int i){return (i - 1)/2;}

        void maxHeapify(int i){

            int l = getLeft(i);
            int r = getRight(i);
            int max = i;

            if(l < heapSize && heap[l] > heap[max])
                max = l;
            if(r < heapSize && heap[r] > heap[max])
                max = r;
            if(max != i){
                swap(heap[max], heap[i]);
                maxHeapify(max);
            }
        }

        void buildMaxHeap(){
            for(int i = heapSize / 2 ; i >=0 ; i--){
                maxHeapify(i);
            }
        }

        void shiftUp(int i){
            while (i > 0 && heap[(i-1) / 2] < heap[i])
            {
                swap(heap[(i-1) / 2], heap[i]);
                i = (i - 1)/2;
            }
            
        }

        void load(ifstream& in){
            string totalToken;
            while (getline(in, totalToken)) {
                if (totalToken.front() == '<')
                    totalToken = totalToken.substr(1);
                if (totalToken.back() == '>')
                    totalToken.pop_back();

                for (char& c : totalToken) {
                    if (c == ',') 
                        c = ' ';
                }

                int k;
                istringstream stream(totalToken);
                while (stream >> k ) {
                    heap.push_back(k);
                }
            }
            heapSize = heap.size();
            buildMaxHeap();
        }

    public:
        MaxHeap(ifstream& in){
            load(in);
            buildMaxHeap();
        }

        void heapSort(){
            buildMaxHeap();
            int size = heapSize;

            for(int i = heapSize - 1; i> 0; i--){
                swap(heap[0], heap[i]);
                heapSize--;
                maxHeapify(0);
            }

            heapSize = size;
        }

        void print(){
            for(int i = 0; i < heap.size(); i++){
                cout << heap[i] << " ";
            }
            cout << endl;
        }

        int search(int key){
            for(int i = 0; i < heap.size(); i++){
                if(heap[i] == key){
                    cout << "elemento: " << key << " trovato all'indice: " << i <<endl;
                    return i;
                }
            }
            cout << "Elemento non trovato"<<endl;
            return -1;
        }

        int extractMax(){
            if(heapSize == 0){
                return -1;
            }

            int max = heap[0];
            swap(heap[0], heap[heapSize - 1]);
            heapSize--;
            heap.pop_back();
            maxHeapify(0);
            return max;
        }

        void increaseKey(int oldKey, int newKey){
            if(oldKey > newKey){
                return;
            }
            int i = search(oldKey);
            heap[i] = newKey;
            
            shiftUp(i);
        }

};



int main(){

    ifstream in("input.txt");

    MaxHeap heap(in);

    heap.print();
    int max = heap.extractMax();
    cout << "Il massimo e' " << max << endl;

    cout<<endl<<  "dopo heap sort"<< endl;

    heap.heapSort();
    heap.print();

    
}

//<20,5,15,30,10,25,2>