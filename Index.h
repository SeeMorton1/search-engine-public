//
// Created by Conner Morton on 11/16/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_INDEX_H
#define SEARCH_ENGINE_LIN_MORTON_INDEX_H

#include <iostream>
#include <list>
#include "DocParser.h"

using namespace std;

class Index {
private:
    string word;
    list<string> IDs;
    int count;
public:
    Index();

    Index(const Index &copy);

    ~Index();

    Index &operator=(const Index &copy);

    void setWord(const string &in);

    void setCount(int i) { count = i; }

    void addCount();

    void addID(const string &id);

    bool operator==(const Index &c);

    bool operator<(const Index &c);

    bool operator>(const Index &c);


    int getCount() {
        string temp;
        for (auto const &i:IDs) {
            if (i != temp) {
                count++;
            }
            temp = i;
        }
        return count;
    }

    string &getWord() {
        return word;
    }

    list<string> &getIDs() {
        return IDs;
    }
    //Index& createIndex(string& w, const DocParser& doc,);
};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEX_H
