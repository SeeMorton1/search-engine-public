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

#include "Query.h"
#include "IndexProcessor.h"


class SearchEngine {
private:

    //HashTable<string,list<string>> authorIndex;
    vector<JsonObject> jsons;
public:
    void setIndex( AvLTree<Index>& copy);
    void setLevel(AvLTree<Index>::AvLNode* node,int level);
    list<string> findDocs(Query& q,AvLTree<Index>& wordIndex);
    static JsonObject& findObjects(const string& ids,vector<JsonObject>& files);
    void setFiles(vector<JsonObject> files);
};


#endif //SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H
