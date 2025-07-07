#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

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
        vector<Item<K, V>*>hash;
        int size;

        void load(ifstream& in){
            string totalTokens;
            while(getline(in, totalTokens)){
                if(totalTokens.front() == '<')
                    totalTokens = totalTokens.substr(1);
                if(totalTokens.back() == '>')
                    totalTokens.pop_back();
                for(char& c : totalTokens){
                    if(c == ','){
                        c = ' ';
                    }
                }
                K k; V v;
                istringstream stream(totalTokens);
                while(stream >> k >> v){
                    insert(k ,v);
                }
            }
        }

    public:
        HashTable(ifstream& in, int s): size(s), hash(s, nullptr){
            load(in);
        }

        int hashingFunc(K key, int i){return (key + i) % size;}

        void insert(K key , V value){
            Item<K,V>* item = new Item<K,V>(key, value);
            int j, i = 0;
            do{
                j = hashingFunc(item->getKey(), i);
                if(hash[j] == nullptr){
                    hash[j] = item;
                    return;
                }
                i++;
            }while(i < size);
        }

        void deleteItem(K key){
            int j, i = 0;
            do{
                j = hashingFunc(key, i);
                if(hash[j] != nullptr && hash[j]->getKey() == key){
                    hash[j] = nullptr;
                    cout << " Elemento cancellato con successo" << endl;
                    return;
                }
                i++;
            }
            while(i < size);
        }

        int search(K key){
            int j, i =0;

            do{
                j = hashingFunc(key, i);
                if(hash[j] != nullptr && hash[j]->getKey() == key){
                    cout << " Elemento trovato all'indice: " << j << endl;
                    return j;
                }
                i++;
            }while(i < size);

            return -1;
        }

        void print(){
            for(int i = 0; i < size; i++){
                if(hash[i] != nullptr){
                    cout << "Key: " << hash[i]->getKey() << " Value: " << hash[i]->getValue() << endl;
                }
                else{
                    cout << "Empty" << endl;
                }
            }
        }

};


int main(){

    ifstream in("input.txt");

    HashTable<int , string> hash(in, 10);

    hash.print();
    cout<<"dopo la delete"<<endl;
    hash.deleteItem(10);
    hash.print();
}