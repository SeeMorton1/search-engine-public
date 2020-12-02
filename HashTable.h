//11/30/2020 I realized that I need hashtable templated so I will implement it, wijth template names K and V for the key and value
//OWNER: Conner Morton
//12/1/2020 restarting again because I realized my way was inefficeint
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
template <typename K, typename V>
struct comp {
    comp(const K& k) : key(k) {}

    bool operator() (const pair<K,V>& p) {
        return (p.first == key);
    }

    K key;
};
template <typename K, typename V>
class HashTable{
public:
    HashTable(int sizeIn = 101):table(sizeIn),size(0){}
    V& operator[](const K& k){
        size_t h= myHash(k);
        vector<pair<K,V>>& l = table[h];
        pairIt it = find_if(l.begin(),l.end(),comp<K,V>(k));
        if(it==l.end()){
            V temp;
            insert(k,temp);
            return this->operator[](k);
        }
        return it->second;

    }
    bool insert(const K& k,const V& v){

        vector< pair<K,V> >& l = table[ myHash(k) ];
        if( find_if(l.begin(), l.end(), comp<K,V>(k)) != l.end() ){
            return false;
        }
        l.push_back(make_pair(k,v));
        if(++size>table.size()){
            rehash();
        }
        return true;
    }
    bool remove(const K& k){
        size_t h = myHash(k);
        vector<pair<K,V>>& l = table[h];
        pairIt it = find_if(l.begin(),l.end(),comp<K,V>(k));
        if(it!=l.end()){
            l.erase(it);
            size--;
            return true;
        }
        return false;
    }

    bool isFound(const K& k)const{
        size_t h = myHash(k);
        const vector< pair<K,V> >& l = table[h];
        bool found = find_if(l.begin(),l.end(),comp<K,V>(k))!=l.end();
        return found;
    }

private:
    vector<vector<pair<K,V>>> table;
    size_t size;
    void clear(){
        for(size_t i = 0;i<table.size();i++){
            table[i].clear();
        }
        size = 0;
    }
    size_t myHash(const K& k)const{
        static hash<K> hasher;
        return (hasher(k)&table.size());
    }
    void rehash(){
        vector<vector<pair<K,V>>> old = table;
        table.resize(2*table.size());
        for(size_t i = 0;i<table.size();i++){
            table[i].clear();
        }
        size = 0;
        for(size_t i = 0;i<old.size();i++){
           for(pairIt it = old[i].begin();it!=old[i].end();it++){
               insert(it->first,it->second);
           }
        }
    }
    typedef typename vector<pair<K,V>>::iterator pairIt;
};

