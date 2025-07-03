#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm> // per reverse

using namespace std;

class MaxHeap {
private:
    vector<int> data;
    int heapSize;

    int getLeft(int i) { return i * 2 + 1; }
    int getRight(int i) { return i * 2 + 2; }

    void maxHeapify(int i) {
        int l = getLeft(i);
        int r = getRight(i);
        int max = i;

        if (l < heapSize && data[l] > data[max])
            max = l;
        if (r < heapSize && data[r] > data[max])
            max = r;

        if (max != i) {
            swap(data[max], data[i]);
            maxHeapify(max);
        }
    }

    void buildMaxHeap() {
        for (int i = heapSize / 2; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    void shiftUp(int i) {
        while (i > 0 && data[(i - 1) / 2] < data[i]) {
            swap(data[(i - 1) / 2], data[i]);
            i = (i - 1) / 2;
        }
    }

public:
    MaxHeap() : heapSize(0) {}

    void load(ifstream& in) {
        string totalToken;
        getline(in, totalToken);
        if (totalToken.front() == '<')
            totalToken = totalToken.substr(1);
        if (totalToken.back() == '>')
            totalToken.pop_back();

        for (char& c : totalToken)
            if (c == ',') c = ' ';

        int k;
        istringstream stream(totalToken);
        while (stream >> k) {
            data.push_back(k);
        }

        heapSize = data.size();
        buildMaxHeap();
    }

    
    int search(int key) {
        for (int i = 0; i < heapSize; i++) {
            if (data[i] == key) {
                cout << "Elemento trovato all' indice: " << i << endl;
                return i;
            }
        }
        return -1;
    }

    int extractMax() {
        if (heapSize == 0)
            return -1;

        int max = data[0];
        swap(data[0], data[heapSize - 1]);
        heapSize--;
        data.pop_back();
        maxHeapify(0);

        return max;
    }

    void heapSort() {
        buildMaxHeap();
        int originalSize = heapSize;
        for (int i = heapSize - 1; i > 0; i--) {
            swap(data[0], data[i]);
            heapSize--;
            maxHeapify(0);
        }
        heapSize = originalSize;
        reverse(data.begin(), data.end());
    }

    void insert(int key) {
        data.push_back(key);
        heapSize++;
        shiftUp(heapSize - 1);
    }

    void increaseKey(int oldKey, int newKey) {
        if (oldKey > newKey)
            return;

        int index = search(oldKey);
        if (index == -1)
            return;

        data[index] = newKey;
        shiftUp(index);
    }

    void print() {
        for (int i = 0; i < data.size(); i++) {
            cout << "Data: " << data[i] << " ";
        }
        cout << "\n";
    }
};

int main() {
    ifstream in("input.txt");

    MaxHeap heap;
    heap.load(in);
    heap.print();

    heap.heapSort();
    heap.print();
    heap.search(30);
    heap.increaseKey(5, 17);
    heap.heapSort();
    heap.print();

    in.close();
    return 0;
}
//<20,5,15,30,10,25,2>
