#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V>
class Item {
private:
  K key;
  V value;

public:
  Item(K key, V value) : key(key), value(value) {}

  K get_key() { return key; }
  V get_value() { return value; }

  void set_key(K key) { this->key = key; }
  void set_value(V value) { this->value = value; }
};

template <typename K, typename V>
class HashTable {
private:
  vector<list<Item<K, V>*>> hash_table;
  int size;

public:
  HashTable(vector<K> keys, vector<V> values, int size) : size(size) {
    hash_table.resize(size);
    for (size_t i = 0; i < keys.size() && i < values.size(); i++) {
      insert(new Item<K, V>(keys[i], values[i]));
    }
  }

  int divide_hashing(K key) { return key % size; }

  // Hashing per moltiplicazione
  int multiply_hashing(K key) {
    double A = (sqrt(5.0) - 1) / 2;
    double product = key * A;
    double fractional = product - floor(product);
    return (int)(size * fractional);
  }

  // Hashing universale (con parametri passati dall'esterno)
  int universal_hashing(K key, int a, int b, int p) {
    return ((a * key + b) % p) % size;
  }

  void insert(Item<K, V>* item) {
    int index = divide_hashing(item->get_key());
    hash_table[index].push_back(item);
  }

  Item<K, V>* search(K key) {
    int index = divide_hashing(key);

    for (auto& item : hash_table[index]) {
      if (item->get_key() == key) {
        cout << "Item [key: " << item->get_key() << " - value: " << item->get_value() << "] found in list with index "
             << index << endl;
        return item;
      }
    }

    cerr << "Item with key " << key << " not found in list with index " << index << endl;
    return nullptr;
  }

  void delete_item(K key) {
    int index = divide_hashing(key);

    for (auto it = hash_table[index].begin(); it != hash_table[index].end(); it++) {
      auto item = (*it);
      if (item->get_key() == key) {
        cout << "Item [key: " << item->get_key() << " - value: " << item->get_value() << "] deleted" << endl;
        hash_table[index].erase(it);
        return;
      }
    }

    cerr << "Item with key " << key << " not deleted" << endl;
  }

  void print() {
    for (int i = 0; i < size; i++) {
      cout << "Index " << i;
      if (hash_table[i].empty()) {
        cout << " -> empty list" << endl;
      } else {
        for (auto& item : hash_table[i]) {
          cout << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }
        cout << endl;
      }
    }
    cout << endl;
  }

  void print(ofstream& out) {
    for (int i = 0; i < size; i++) {
      out << "Index " << i;
      if (hash_table[i].empty()) {
        out << " -> empty list" << endl;
      } else {
        for (auto& item : hash_table[i]) {
          out << " -> [key: " << item->get_key() << " - value: " << item->get_value() << "]";
        }
        out << endl;
      }
    }
    out << endl;
  }
};

// Funzione per leggere i token tra < >
template <typename T>
vector<T> read_tokens_between_brackets(ifstream& file) {
  vector<T> result;
  string line;

  while (getline(file, line)) {
    istringstream iss(line);
    string token;

    while (iss >> token) {
      if (token.front() == '<' && token.back() == '>') {
        token = token.substr(1, token.length() - 2);
        istringstream converter(token);
        T value;
        converter >> value;
        result.push_back(value);
      }
    }
  }

  return result;
}

int main() {
  ifstream keys_file("keys.txt");
  ifstream values_file("values.txt");
  ofstream output_file("output.txt");

  if (!keys_file || !values_file) {
    cerr << "Errore nell'apertura dei file di input." << endl;
    return 1;
  }

  vector<int> keys = read_tokens_between_brackets<int>(keys_file);
  vector<string> values = read_tokens_between_brackets<string>(values_file);

  HashTable<int, string> ht(keys, values, 10);

  ht.print();
  ht.print(output_file);

  ht.search(8);
  ht.delete_item(8);

  cout << endl << "After delete" << endl;
  output_file << endl << "After delete" << endl;
  ht.print();
  ht.print(output_file);

  keys_file.close();
  values_file.close();
  output_file.close();

  return 0;
}
