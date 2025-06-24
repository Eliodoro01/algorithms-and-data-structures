#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

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
class HashTable {
private:
    vector<Item<K,V>*> hash_table;
    int size;

public:
    HashTable(ifstream& in , int s) : size(s) {
        hash_table.resize(size, nullptr); // inizializza a nullptr

        K key; V value;
        while(in >> key >> value)
            insert(new Item<K, V>(key, value));
    }

    int hash(K key, int i) { 
        return (key + i) % size; 
    }

    int quadraticHash(int key, int i) {
        return (key + i*i) % size; // oppure (key + c1*i + c2*i*i)
    }

    int doubleHash(int key, int i) {
        int hash1 = key % size;
        int hash2 = 1 + (key % (size - 1));
        return (hash1 + i * hash2) % size;
    }

    void insert(Item<K,V>* item) {
        int i = 0, j;

        do {
            j = hash(item->getKey(), i);
            if(hash_table[j] == nullptr) {
                hash_table[j] = item;
                return;
            }
            i++;
        } while(i != size);

        cout << "Error: overflow" << endl;
    }

    void delete_hash(K key) {
        int i = 0, j;

        do {
            j = hash(key, i);
            if(hash_table[j] == nullptr)
                return;
            if(hash_table[j]->getKey() == key) {
                hash_table[j] = nullptr;
                return;
            }
            i++;
        } while(i != size);

        cout << "Elemento non trovato" << endl;
    }

    int find_hash(K key) {
        int i = 0, j;

        do {
            j = hash(key, i);
            if(hash_table[j] == nullptr)
                return -1;
            if(hash_table[j]->getKey() == key) {
                cout << "Elemento trovato con valore: " << hash_table[j]->getValue() << endl;
                return j;
            }
            i++;
        } while(i != size);

        cout << "Elemento non trovato" << endl;
        return -1;
    }

    void print() {
        for(int i = 0; i < size; i++) {
            if(hash_table[i] != nullptr)
                cout << "Index " << i << ": Key = " << hash_table[i]->getKey() << ", Value = " << hash_table[i]->getValue() << endl;
            else
                cout << "Index " << i << ": empty" << endl;
        }
    }
};


int main() {
    ifstream in("input.txt");
    HashTable<int, string> ht(in, 10);

    ht.find_hash(5);
    ht.delete_hash(5);
    ht.print();

    in.close();
    return 0;
}