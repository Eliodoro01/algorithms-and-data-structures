#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

template<typename K, typename V>
class Item{

    private:
        K key;
        V value;

    public:
        Item(K k, V v): key(k), value(v){}

        void setKey(K k){key = k;}
        void setValue(V v){value = v;}

        K getKey(){return key;}
        V getValue(){return value;}
};

template<typename K, typename V>
class HashTable{

    private:
        vector<Item<K,V>*> table;
        int size;

        void load(ifstream& in1, ifstream& in2){
            string keyLine, valueLine;
            while(getline(in1, keyLine) && getline(in2, valueLine)){
                if(keyLine.front() == '<')
                    keyLine = keyLine.substr(1);
                if(keyLine.back() == '>')
                    keyLine.pop_back();
                for(char& c : keyLine){
                    if(c == ',')
                        c = ' ';
                }
                istringstream keyStream(keyLine);
                K k;
                keyStream >> k;

                if(valueLine.front() == '<')
                    valueLine = valueLine.substr(1);
                if(valueLine.back() == '>')
                    valueLine.pop_back();
                for(char& c : valueLine){
                    if(c == ',')
                        c = ' ';
                }
                istringstream valueStream(valueLine);
                V v;
                valueStream >> v;

                insert(new Item<K, V>(k, v));
            }
        }

        int hashFunc(K key, int i){
            return (key + i) % size;
        }

    public:
        HashTable(ifstream& in1, ifstream& in2, int s) : size(s), table(s, nullptr){
            load(in1,in2);
        }

        void insert(Item<K, V>* item){
            int j, i = 0;
            do{
                j = hashFunc(item->getKey(), i);
                if(table[j] == nullptr){
                    table[j] = item;
                    break;
                }
                i++;
            }while(i<size);
        }

        void deleteItem(Item<K,V>* item){
            int j , i = 0;

            do{
                j = hashFunc(item->getKey(), i);
                if(table[j] != nullptr && table[j]->getKey() == item->getKey()){
                    table[j] = nullptr;
                    cout << "Elemento cancellato con successo" << endl;
                    break;
                }
                i++;
            }
            while(i < size);
        }

        int searchItem(Item<K,V>* item){

            int j, i = 0;
            do{
                j = hashFunc(item->getKey(), i);
                if(table[j] != nullptr && table[j]->getKey() == item->getKey()){
                    cout << "Elemento trovato all' indice: "<< j << endl;
                    return j;
                }
                i++;
            }while(i < size);
            cout << "Elemento non trovato" << endl;
            
        }


        void print(){
            for(int i = 0; i < table.size(); i++){
                if(table[i] != nullptr)
                    cout << "Key -> " << table[i]->getKey() << " Value -> " << table[i]->getValue() << endl;
                else
                    cout << "Empty" << endl;
            }
        }

};

int main(){

    ifstream in1("input.txt");
    ifstream in2("input2.txt");

    
    HashTable<int, string> hash(in1, in2, 10);

    hash.print();
    
    Item<int, string>* item = new Item<int, string>(20, "pippo");
    
    hash.searchItem(item);

    hash.deleteItem(item);
    hash.print();
    
}
/*<20>
<30>
<10>
<5>
<15>

<pippo>
<pluto>
<prova>
<test>
<lol>*/
