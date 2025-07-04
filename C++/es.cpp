#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <sstream>

using namespace std;

template<typename K, typename V>
class Item {
private:
    K key;
    V value;

public:
    Item(K k, V v) : key(k), value(v) {}
    K getKey() { return key; }
    V getValue() { return value; }
};

template<typename K, typename V>
class Hash {
private:
    vector<list<Item<K,V>*>> hash;
    int size;

    int hashFunc(K key, int i) {
        return (key * i) % size;
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
                insert(new Item<K, V>(k, v));
            }
        }
    }

public:
    Hash(ifstream& in, int s) : size(s) {
        hash = vector<list<Item<K,V>*>>(s); // liste vuote
        load(in);
    }

    void insert(Item<K,V>* item) {
        int index = hashFunc(item->getKey(), 1); // i arbitrario
        hash[index].push_back(item);
    }

    int search(K key, int i) {
        int index = hashFunc(key, i);
        for (auto& item : hash[index]) {
            if (item->getKey() == key) {
                cout << "Item [key: " << item->getKey() << " - value: " << item->getValue() << "] found at index " << index << endl;
                return index;
            }
        }
        cout << "Key not found\n";
        return -1;
    }

    void deleteItem(K key, int i) {
        int index = hashFunc(key, i);
        for (auto it = hash[index].begin(); it != hash[index].end(); ++it) {
            auto item = *it;
            if (item->getKey() == key) {
                cout << "Item [key: " << item->getKey() << " - value: " << item->getValue() << "] deleted\n";
                hash[index].erase(it);
                return;
            }
        }
        cout << "Key not found for deletion\n";
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i;
            if (hash[i].empty()) {
                cout << " -> empty list" << endl;
            } else {
                for (auto& item : hash[i]) {
                    cout << " -> [key: " << item->getKey() << " - value: " << item->getValue() << "]";
                }
                cout << endl;
            }
        }
    }
};

int main() {
    ifstream in("input.txt");
    if (!in.is_open()) {
        cerr << "Errore apertura file input." << endl;
        return 1;
    }

    int tableSize = 5;

    Hash<int, string> hash(in, tableSize);

    hash.print();

    hash.search(20, 1);

    hash.deleteItem(10, 1);

    hash.print();

    in.close();
    return 0;
}
