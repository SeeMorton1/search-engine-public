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
    list<pair<size_t, list<string>>> table;
public:
    HashTable(){
        capacity=0;
    }
    int calcCap() {
        capacity= table.size();
        return table.size();
    }

    pair<size_t, list<string>> at(int n);





    bool isEmtpy()const;

    void insertItem(const string &key, const string &value);

    void removeItem(const int &key);
  //  V& searchTable(const K& key);
//    void printTable();
};

pair<size_t, list<string>> HashTable::at(int n) {
    auto it = table.begin();
    if (n < table.size() && n > 0) {
        advance(it, n);
        pair<size_t, list<string>> p;
        p.first = it->first;
        p.second = it->second;
        return p;
    } else {
        cout << "out of range" << endl;
        pair<size_t, list<string>> p;
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
    bool exists = false;
    for (auto &it : table) {

        if (it.first == hashVal) {
            exists = true;
            it.second.push_back(value);
        }
    }
    if (!exists) {
        pair<size_t, list<string>> p;
        list<string> ll;
        ll.push_back(value);
        p.second = ll;
        p.first = hashVal;
        table.push_back(p);
    }


}

void HashTable::removeItem(const int &key) {

}

#endif //SEARCH_ENGINE_LIN_MORTON_HASHTABLE_H

// TODO  Make the list actually a pair of ints for the hash code and the list of strings for the IDS
// 0|List<ids>
// 1|list<ids>
//This works by assigning a has to a string. THIS WORKS

