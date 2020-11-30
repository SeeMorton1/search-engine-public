//
// Created by Conner Morton on 11/26/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H
#define SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H

#include <string>
#include <iostream>
#include "Query.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include "AvLTree.h"
#include "Index.h"
#include "DocParser.h"
#include "JsonObject.h"
using namespace std;

class QueryProcessor {
private:
    string search;
    Query query;
public:
    QueryProcessor() = default;

    ~QueryProcessor() = default;

    QueryProcessor(const QueryProcessor &copy) = default;

    void genQuery();
    list<string>& findId(DocParser& doc);


    void setSearch(const string &in);
};


#endif //SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H
