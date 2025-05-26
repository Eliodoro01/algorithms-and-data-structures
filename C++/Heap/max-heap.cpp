#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void maxHeapify(int i, int heapSize) {
        int l = 2 * i + 1; // figlio sinistro
        int r = 2 * i + 2; // figlio destro
        int max = i;

        if (l < heapSize && heap[l] > heap[max]) {
            max = l;
        }

        if (r < heapSize && heap[r] > heap[max]) {
            max = r;
        }

        if (max != i) {
            swap(heap[i], heap[max]);
            maxHeapify(max, heapSize);
        }
    }

public:
    MaxHeap(const vector<int>& data) {
        heap = data;
        buildMaxHeap();
    }

    void buildMaxHeap() {
        int heapSize = heap.size();
        for (int i = heapSize / 2 - 1; i >= 0; i--) {
            maxHeapify(i, heapSize);
        }
    }

    void printHeap() const {
        for (int val : heap) {
            cout << val << " ";
        }
        cout << endl;
    }

    const vector<int>& getHeap() const {
        return heap;
    }
};



int main() {
    vector<int> data = {4, 10, 3, 5, 1};

    MaxHeap mh(data);

    cout << "Heap costruito: ";
    mh.printHeap();

    return 0;
}
