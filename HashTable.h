//11/30/2020 I realized that I need hashtable templated so I will implement it, wijth template names K and V for the key and value
//OWNER: Conner Morton
//12/1/2020 restarting again because I realized my way was inefficeint
//12/6/2020 Not understanding why I made it a vector<vector<pairs> so I will change that to make it simpler
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
const int init = 10000;
template<typename K, typename V>
class HashTable{
private:
    vector<pair<K,vector<V>>> table;
    long size= 0;
public:
    HashTable(){
        for(int i =0;i<init;i++) {
            pair<K,vector<V>> p;
            table.push_back(p);
        }
    }

    ~HashTable()= default;

    //getters
    long getHash(K& k){
        hash<K> hasherslasher;
        return hasherslasher(k)%init;
    }
    pair<K,vector<V>>& getPair(K& k){
        return table[getHash(k)];
    }

    vector<pair<K,vector<V>>> getTable(){
        return table;
    }
    long getSize(){
        return size;
    }
    void clear(){
        table.clear();
    }
    void insert(K& k, V& v){
        long h = getHash(k);

        if(table.at(h).second.empty()){
            size++;
            vector<V> values;
            values.push_back(v);
            table.at(h) = make_pair(k,values);
        }else {
            table.at(h).second.push_back(v);
        }
    }

};
