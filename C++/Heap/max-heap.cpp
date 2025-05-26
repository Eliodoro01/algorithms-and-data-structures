#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    int left(int i) const {
        return 2 * i + 1;
    }

    int right(int i) const {
        return 2 * i + 2;
    }

    int parent(int i) const {
        return (i - 1) / 2;
    }

    void maxHeapify(int i, int heapSize) {
        int l = left(i);
        int r = right(i);
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
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            maxHeapify(i, heap.size());
        }
    }

    void heapSort() {
        int heapSize = heap.size();
        buildMaxHeap(); // assicuriamoci che l'heap sia valido

        for (int i = heapSize - 1; i >= 1; i--) {
            swap(heap[0], heap[i]); // sposta il massimo alla fine
            heapSize--;             // riduci la dimensione dell'heap
            maxHeapify(0, heapSize);
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

    // accesso diretto (opzionale)
    int getParentIndex(int i) const { return parent(i); }
    int getLeftIndex(int i) const { return left(i); }
    int getRightIndex(int i) const { return right(i); }
};



int main() {
    vector<int> data = {4, 10, 3, 5, 1};

    MaxHeap mh(data);

    cout << "Heap costruito: ";
    mh.printHeap();

    mh.heapSort();

    cout << "Array ordinato (Heap Sort): ";
    mh.printHeap();

    return 0;
}

