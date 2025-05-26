#include <iostream>
#include <vector>

using namespace std;


class MaxHeap{

  private:
    vector<int> heap;

    void maxHeapify( int i){
        int l = (i * 2) + 1;
        int r = (i * 2) + 2; 
        int max = i;

        if(l < heap.size() && heap[l] < heap[max]){
            max = l;
        }

        if(r < heap.size() && heap[r] < heap[max]){
            max = r;
        }

        if(max != i){
            swap(heap[i], heap[max]);
            maxHeapify(max);
        }

    }

  public:

    MaxHeap(const vector<int>& data){
        heap = data;
        buildMaxHeap();
    }

    void buildMaxHeap(){
        for(int i = heap.size() /2 -1; i >= 0; i--){
            maxHeapify(i);
        }
    }

};

