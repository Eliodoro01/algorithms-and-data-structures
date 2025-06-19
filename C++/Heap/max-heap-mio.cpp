#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class MaxHeap{

    private:
        vector<int> heap;

        int getLeft(int i) const{
            return 2 * i + 1;
        }

        int getRight(int i) const{
            return 2 * i +2;
        }

        int getParent(int i)const{
            return (i - 1) / 2;
        }

        void maxHeapify(int i, int heapSize){

            int l = getLeft(i);
            int r = getRight(i);
            int max = i;

            if(l < heapSize && heap[l] > heap[max]){
                max = l;
            }
            if(r < heapSize && heap[r] > heap[max]){
                max = r;
            }
            if(max != i){
                swap(heap[i], heap[max]);
                maxHeapify(max, heapSize);
            }
        }

    public:

        MaxHeap(const vector<int>& data){heap =data; buildMaxHeap();}
        
        void buildMaxHeap(){
            for(int i = heap.size() / 2 - 1; i >= 0; i--){
                maxHeapify(i, heap.size());
            }
        }

        void heapSort(){
            int heapSize = heap.size();
            buildMaxHeap();

            for(int i = heapSize - 1; i>= 1; i--){
                swap(heap[0], heap[i]);
                heapSize--;
                maxHeapify(0, heapSize);
            }
        }

        void printHeap()const{
            for(int val : heap){
                cout<<val<< " ";
            }
            cout << endl;
        }

        const vector<int>& getHeap() const{
            return heap;
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

    return 0;

}