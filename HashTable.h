//11/30/2020 I realized that I need hashtable templated so I will implement it, wijth template names K and V for the key and value
//OWNER: Conner Morton
//12/1/2020 restarting again because I realized my way was inefficeint
//12/6/2020 Not understanding why I made it a vector<vector<pairs> so I will change that to make it simpler
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
const int init = 5000;
template<typename K, typename V>
class HashTable{
private:
    vector<pair<K,vector<V>>> table;
    long size= 0;
public:
    HashTable();
    HashTable(int n);
    ~HashTable();

    //getters
    long getHash(K& k){
        hash<K> hasherslasher;
        return hasherslasher(k)%init;
    }
    pair<K,V>& getPair(K& k, V& v);
    long getSize(){
        return size;
    }
    void insert(K& k, V& v){
        long h = getHash(k);
        size++;
        vector<V> values;
        values.push_back(v);
        table.at(h) = make_pair(k,values);


    }

};
