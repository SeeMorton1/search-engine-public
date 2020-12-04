//
// Created by zihao on 12/3/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_TOPWORDSOBJECT_H
#define SEARCH_ENGINE_LIN_MORTON_TOPWORDSOBJECT_H
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class TopWordsObject {
private:
    string word;
    int count;
public:
    TopWordsObject();
    ~TopWordsObject();
    TopWordsObject(const TopWordsObject& copy);

    void setWord(string w);
    void setCount(int c);

    string returnWord();
    int returnCount();


};


#endif //SEARCH_ENGINE_LIN_MORTON_TOPWORDSOBJECT_H
