//
// Created by Conner Morton on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_HASHTABLE_H
#define SEARCH_ENGINE_LIN_MORTON_HASHTABLE_H

#include <iostream>
#include <list>
#include <string>
#include "Index.h"
#include <functional>
#include "xxhash-master/xxhash64.h"
using namespace std;



class HashNode{
public:
    list<string> values;
    string key;
    HashNode(const string& key, const list<string>& value){
        this->values= value;
        this->key = key;
    }

};


class HashTable{
private:
    int capacity;
    list<pair<string,list<string>>> table;
public:
    HashTable(){
        capacity=0;
    }
    int calcCap() {
        capacity= table.size();
        return table.size();
    }
    pair<string,list<string>> at(int n);





    bool isEmtpy()const;
    void insertItem(const string& key, const string& value);
  //  void removeItem(const K& key);
  //  V& searchTable(const K& key);
//    void printTable();
};

pair<string,list<string>> HashTable::at(int n) {
    auto it = table.begin();
    if(n<table.size()&&n>0){
        advance(it,n);
        pair<string,list<string>> p;
        p.first=it->first;
        p.second= it->second;
        return p;
    }else{
        cout<<"out of range"<<endl;
        pair<string,list<string>> p;
        p.first=table.begin()->first;
        p.second=table.begin()->second;
        return p;
    }

}


bool HashTable::isEmtpy() const {
    return table.empty();
}

void HashTable::insertItem(const string &key, const string &value) {
    hash<string> str_hash;
    size_t hashVal = str_hash(key);

    auto& cell = table.;


}

#endif //SEARCH_ENGINE_LIN_MORTON_HASHTABLE_H
