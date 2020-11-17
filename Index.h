//
// Created by Conner Morton on 11/16/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_INDEX_H
#define SEARCH_ENGINE_LIN_MORTON_INDEX_H

#include <iostream>
#include <list>

using namespace std;

class Index {
private:
    string word;
    list<int> IDs;
    int count;
public:
    Index();

    Index(const Index &copy);

    ~Index();

    Index &operator=(const Index &copy);

    void setWord(const string &in);

    void addCount();

    void addID(int id);

    bool operator==(const Index &c);

    bool operator<(const Index &c);

    bool operator>(const Index &c);


    int getCount() {
        int temp = 0;
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

    list<int> &getIDs() {
        return IDs;
    }
};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEX_H
