#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class MaxHeap{

    private:
        vector<int> data;
        int heapSize;

        void load(ifstream& in){
            string totalToken;
            while(getline(in, totalToken)){
                if(totalToken.front() == '<')
                    totalToken = totalToken.substr(1);
                if(totalToken.back() == '>')
                    totalToken.pop_back();
                for(char& c : totalToken){
                    if(c == ',')
                        c = ' ';
                }

                int k;
                istringstream stream(totalToken);

                while(stream >> k){
                    data.push_back(k);
                }
                heapSize = data.size();
                buildMaxHeap();
            }
        }

        void maxHeapify(int i){

            int l = (i*2) + 1;
            int r = (i*2) + 2;
            int max = i;

            if(l < heapSize && data[l] > data[max])
                max = l;
            if(r < heapSize && data[r] > data[max])
                max = r;
            if(max != i){
                swap(data[max], data[i]);
                maxHeapify(max);
            }
        }

        void buildMaxHeap(){
            for(int i = (heapSize / 2) - 1; i >= 0; i--){
                maxHeapify(i);
            }
        }

        int search(int key){

            for(int i = 0; i < data.size(); i++){
                if(data[i] == key){
                    return i;
                }
            }
            cout << "Elemento non trovato" << endl;
            return -1;
        }

        void shiftUp(int i){
            while(data[(i - 1) /2] < data[i]){
                swap(data[(i-1)/2], data[i]);
                i = (i-1)/2;
            }
        }



    public:
        MaxHeap(ifstream& in, vector<int>& d) : heapSize(d.size()), data(d){
            load(in);
        }

        void heapSort(){

            buildMaxHeap();
            int originalSize = data.size();

            for(int i = heapSize - 1; i > 0; i--){
                swap(data[0], data[i]);
                heapSize--;
                maxHeapify(0);
            }

            heapSize = originalSize;
        }

        int extractMax(){
            buildMaxHeap();
            int max = data[0];
            swap(data[0], data[heapSize - 1]);
            heapSize--;
            maxHeapify(0);

            return max;
        }

        void print(){
            for(int i = 0; i < data.size(); i++){
                cout << data[i] << " ";
            }
            cout << endl;
        }

        void increaseKey(int oldKey, int newKey){

            int index = search(oldKey);
            data[index] = newKey;

            shiftUp(index);
        }

};

int main(){

    ifstream in("input.txt");

    vector<int> data;

    MaxHeap heap(in, data);

    int max = heap.extractMax();

    cout << "Il max e': " << max << endl;

    heap.print();

    heap.heapSort();

    heap.print();

    heap.increaseKey(3, 5);

    heap.print();

}