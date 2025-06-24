#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <math.h>


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

        void setKey(K k){key = k;}
        void setValue(V v){value = v;} 
};

template<typename K, typename V>
class HashTable{

    private:
        vector<list<Item<K,V>*>> hash_table;
        int size;
    
    public:
        HashTable(ifstream& in, int size) : size(size){
            hash_table.resize(size);

            K key;
            V value;
            while(in >> key >> value) 
                insert(new Item<K, V>(key, value));
        }

        int divideHashing(K key){return key % size;}
        int multiply_hashing(K key) {
            double A = (sqrt(5.0) - 1) / 2;       // Costante A corretta come double
            double product = key * A;             // Moltiplicazione
            double frac = product - floor(product); // Parte frazionaria
            return floor(size * frac);           // Indice finale
        }

        void insert(Item<K, V>* item){
            int index = divideHashing(item->getKey());
            hash_table[index].push_back(item);
        }

        Item<K, V>* search(K key){
            int index = divideHashing(key);

            for(auto& item : hash_table[index]){
                if(item->getKey() == key){
                    cout<< "Item [key: " << item->getKey() << " - value" << item->getValue() << "] found at index" << index << endl; 
                    return  item;
                }
            }

            cerr<<"Item with key " << key << "not found in list with index" << index<<endl;
            return nullptr;
        }

        void delete_item(int key){
            int index = divideHashing(key);

            for(auto it = hash_table[index].begin(); it!= hash_table[index].end(); it++){
                auto item = (*it);
                if(item->getKey() == key){
                    cout << "Item [key: " << item->getKey() << " - value: " << item->getValue() << "] deleted" << endl;
                    hash_table[index].erase(it);
                    return;
                }
            }
            cerr << "Item with key " << key << "not deleted" << endl;
            return;
        }

        void print(){
            for(int i = 0; i < size; i++){
                cout<< " Index" << i;
                if(hash_table[i].empty()){
                    cout << " -> empty list" << endl;
                }
                else{
                    for(auto& item: hash_table[i]){
                        cout<< " -> [key: " << item->getKey() << " - value: "<< item->getValue() <<"]";
                    }
                    cout << endl;

                }
            }
            cout<<endl;
        }

};

int main(void) {
  ifstream input_file("input.txt");
  ofstream output_file("output.txt");

  HashTable<int, string> ht(input_file, 10);
  ht.print();
  //ht.print(output_file);

  ht.search(8);
  ht.delete_item(8);

  cout << endl << "After delete" << endl;
  output_file << endl << "After delete" << endl;
  ht.print();
  //ht.print(output_file);

  input_file.close();
  output_file.close();

  return 0;
}