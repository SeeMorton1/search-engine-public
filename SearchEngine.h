//
// Created by Conner Morton on 11/30/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H
#define SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H


#include <iostream>
#include <string>
#include <list>
#include "AvLTree.h"
#include "Index.h"
#include "HashTable.h"
class SearchEngine {
private:
    AvLTree<Index> wordIndex;
    HashTable<string,list<string>> authorIndex;
public:
    
};


#endif //SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H
