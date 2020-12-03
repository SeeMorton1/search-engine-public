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
#include "Query.h"
class SearchEngine {
private:
    AvLTree<Index> wordIndex;
    HashTable<string,list<string>> authorIndex;
    vector<JsonObject> jsons;
public:
    void popIndex(const DocParser& doc);
    list<string> findDocs(Query& q);
    static JsonObject& findObjects(const string& ids,vector<JsonObject>& files);
    void setFiles(vector<JsonObject>& files);
};


#endif //SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H
