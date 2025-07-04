#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sstream>

using namespace std;

template<typename K, typename V>
class Item{

    private:
        K key;
        V value;

    public:

        Item(K k, V v) : key(k), value(v){}

        K getKey(){return key;}
        V getValue(){return value;}
};


template<typename K, typename V>
class Hash {
private:
    vector<Item<K,V>*> hash;
    int size;

    int hashFunc(K key, int i) {
        return (key + i) % size; // sondatura lineare
    }

    int quadraticHash(int key, int i){
        return (key + i * i) % size;
    }

    void load(ifstream& in) {
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

            K k;
            V v;
            istringstream stream(totalToken);
            while (stream >> k >> v) {
                insert(new Item<K,V>(k, v));
            }
        }
    }

public:
    Hash(ifstream& in, int s) : size(s) {
        hash = vector<Item<K,V>*>(size, nullptr); // inizializza hash table
        load(in);
    }


    void insert(Item<K,V>* item) {
        int i = 0;
        int j;

        do {
            j = hashFunc(item->getKey(), i);
            if (hash[j] == nullptr) {
                hash[j] = item;
                return;
            }
            i++;
        } while (i < size);
    }

    void deleteItem(K key) {
        int i = 0, j;
        do {
            j = hashFunc(key, i);
            if (hash[j] != nullptr && hash[j]->getKey() == key) {
                hash[j] = nullptr;
                return;
            }
            i++;
        } while (i < size);
    }

    int search(K key) {
        int i = 0, j;
        do {
            j = hashFunc(key, i);
            if (hash[j] != nullptr && hash[j]->getKey() == key) {
                cout << "Chiave trovata all'indice: " << j << endl;
                return j;
            }
            i++;
        } while (i < size);

        cout << "Chiave non trovata." << endl;
        return -1;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            if (hash[i] != nullptr) {
                cout << "Index " << i << " key: " << hash[i]->getKey()
                     << " value: " << hash[i]->getValue() << endl;
            } else {
                cout << "Index " << i << " empty" << endl;
            }
        }
    }
};



int main() {
    ifstream in("input.txt");

    Hash<int, string> hash(in, 11);

    hash.search(20);
    hash.print();
    hash.insert(new Item<int, string>(30, "mamma"));
    hash.print();

    in.close();
}
/*<20, pippo>
<11, cazzo>
<30, antonio>
<1, peppe>
<10, elmasgrande>*/
