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
#include <fstream>
#include "Query.h"
#include "IndexProcessor.h"


class SearchEngine {
private:
    Query query;
    //HashTable<string,list<string>> authorIndex;
    vector<JsonObject> jsons;
public:
    void setIndex( AvLTree<Index>& copy);
    void setQuery(Query q){query = q;}
    void setArgs(const char* c, ifstream stop, ifstream csv);
    void setLevel(AvLTree<Index>::AvLNode* node,int level);
    list<string> findDocs(Query& q,AvLTree<Index>& wordIndex,const char* file, ifstream& stop, ifstream& csv);
    JsonObject findObjects(const string& ids);
    void setFiles(vector<JsonObject> files);
    vector<JsonObject> getJsons(){
        return jsons;
    }
    void populateJsons(Query q,AvLTree<Index> wordIndex, const char* file, ifstream& stop,ifstream& csv);
    static JsonObject findFile(string id,const char* file,ifstream& stop, ifstream& csv);
};


#endif //SEARCH_ENGINE_LIN_MORTON_SEARCHENGINE_H
