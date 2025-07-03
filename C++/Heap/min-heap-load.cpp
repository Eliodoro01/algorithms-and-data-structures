#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


class MinHeap{

    private:
        vector<int> data;
        int heapSize;

        int getRight(int i){
            return 2 * i + 2;
        }

        int getLeft(int i ){
            return 2 * i + 1;
        }

        void builMinHeap(){
            for(int i = heapSize / 2; i >= 0; i--){
                minHeapify(i);
            }
        }

        void minHeapify(int i){
            int l = getLeft(i);
            int r = getRight(i);
            int min = i;

            if(l < heapSize && data[l] < data[min])
                min = l;
            if(r < heapSize && data[r] < data[min])
                min = r;

            if(min != i){
                swap(data[min], data[i]);
                minHeapify(min);
            }
        }

        void shiftUp(int i){
            while(i > 0 && data[(i - 1) / 2] > data[i]){
                swap(data[(i-1)/2], data[i]);
                i = (i-1)/2;
            }
        }

        int search(int key){
            for(int i = 0; i < heapSize; i++){
                if(data[i] == key){
                    return i;
                }
            }
            return -1;
        }

    
    public:
        MinHeap(vector<int>& values): data(values), heapSize(data.size()){builMinHeap();}
        
        void insert(int key){
            heapSize++;
            data.push_back(key);

            int i = heapSize - 1;
            shiftUp(i);
        }

        void print(ofstream& out){
            for(int i = 0; i < data.size(); i++){
                cout << "Data: " << data[i] << " ";
            }
            cout << "\n";
        }

        void decreaseKey(int oldKey, int newKey){

            if(newKey > oldKey){
                return;
            }

            int index = search(oldKey);

            if(index == -1){
                return;
            }

            data[index] = newKey;

            shiftUp(index);

        }

        void heapSort(){
            builMinHeap();
            for(int i = heapSize - 1; i > 0; i--){
                swap(data[0], data[i]);
                heapSize--;
                minHeapify(0);
            }
        }

        int extractMin(){
            if(heapSize == 0){
                return -1;
            }

            int min = data[0];
            swap(data[0], data[heapSize - 1]);
            heapSize--;
            data.pop_back();
            minHeapify(0);

            return min;
        }


        void loadFile(ifstream& in){

            string totalToken;
            getline(in, totalToken);

            if(totalToken.front() == '<')
                totalToken = totalToken.substr(1);
            if(totalToken.back() == '>')
                totalToken.pop_back();

            for(char& c : totalToken){
                if(c == ','){
                    c = ' ';
                }
            }

            int k;
            istringstream stream(totalToken);
            while(stream >> k){
                data.push_back(k);
            }

            heapSize = data.size();
            builMinHeap();
        }


};


int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    vector<int> values;

    MinHeap heap(values);

    heap.loadFile(in);
    heap.print(out);
    heap.heapSort();
    heap.print(out);

    in.close();
    out.close();

}
//input.txt
//<20,5,15,30,10,25,2>