#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

template <typename T, typename X>

class item{
    private:
        T key;
        X value;
    
    public:
        item(T key, X value) : key(key), value(value){}

        T getKey(){ return key;}
        X getValue(){ return value;}
};

template <typename T, typename X>

class hashTable{

    private:
        vector<item<T,X>*> table;
        int tableSize;
    
    public:
        hashTable(int m) : tableSize(m) { table.resize(m, nullptr)};

        int hash(T key, int i){return (key + i) % tableSize;}
        int quadraticHash(int key, int i){return (key + i + i*i) % tableSize;}

        int doubleHash(int key, int i){
            int hash1 = key % tableSize;
            int hash2 = 1 + (key % (tableSize - 1));
            return (hash1 + i * hash2) % tableSize;
        }

        void insert(item<T,X>* item){
            int i = 0;
            int j; 

            do{
                j = hash(item->getKey(), i);

                if(table[j] == nullptr){
                    table[j] = item;
                    return;
                }
                else
                    i++;
            }
            while(i != tableSize);

            cout << "Error overflow!"<<endl;
        }

        void print(ofstream& out){
            for(int i = 0; i < tableSize; i++){
                if(table[i] != nullptr)
                    out << "Index: " << i << ", key: " << table[i]->getKey()<< ", value: " << table[i]->getValue() << endl;
                
            }
        }

        string find(T key){

            int i = 0;
            int j;

            do{
                j = hash(key, i);

                if(table[j]->getValue() == key)
                    return table[j]->getValue();

                if(table[j] == nullptr)
                    continue;

                i++
            }
            while(table[j] != nullptr && i != tableSize);

            return "";
        }

        /*
        int find(T key){
            int i = 0;
            int j;

            do{
                j = hash(key, i);

                if(table[j] == nullptr)
                    continue;
                if(table[j]->getKey() == key)
                    return table[j]->getValue();

                i++;
            }while (table[j] != nullptr && i != tableSize);

            return -1
        }
        */

        void Delete(T key){

            int i = 0;
            int j;

            do{
                j = hash(key, i);

                if(table[j] == nullptr)
                    continue;
                
                if(table[j]->getKey() == key){
                    table[j] = nullptr;

                    cout << "Hash table dopo l'eliminazione:" << endl;
                    for(int i = 0; i < tableSize; i++)
                        if(table[i] != nullptr)
                            cout<< "Index: " << i << ", key:" << table[i]->getKey() << ", value: "<< table[j]->getKey() << endl;
                        
                        
                    return;
                }

                i++;
            }while(table[j] != nullptr && i != tableSize);
        }
};


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    hashTable<int,string> ht(10);

    while (!in.eof()) {
        int i;
        string s;
        in >> i >> s;
        item<int, string>* newItem = new item<int, string>(i, s);
        ht.insert(newItem);
    }

    /*
    hashTable<char,int> ht(10);

    while (!in.eof()) {
        char i;
        int s;
        in >> i >> s;
        item<char, int>* newItem = new item<char, int>(i, s);
        ht.insert(newItem);
    }
    */

    ht.print(out);

    in.close();
    out.close();

    int keySearched = 6;
    string str = ht.find(keySearched);

    if (str.length() == 0)
        cout << "La stringa con chiave " << keySearched << " non è stata trovata!" << endl << endl;
    else
        cout << "La stringa associata alla chiave " << keySearched << " è '" << str << "'!" << endl << endl;

    /*
    char keySearched = 'u';
    int i = ht.find(keySearched);

    if (i == -1)
        cout << "L'intero con chiave " << keySearched << " non è stato trovato!" << endl << endl;
    else
        cout << "L'intero associato alla chiave " << keySearched << " è '" << i << "'!" << endl << endl;
    */

    ht.Delete(12);

    return 0;
}