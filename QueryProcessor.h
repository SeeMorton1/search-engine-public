//
// Created by Conner Morton on 11/26/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H
#define SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H

#include <string>
#include <iostream>
#include "Query.h"

using namespace std;

class QueryProcessor {
private:
    string search;
public:
    QueryProcessor() = default;

    ~QueryProcessor() = default;

    QueryProcessor(const QueryProcessor &copy) = default;

    Query &genQuery();

    void setSearch(const string &in);
};


#endif //SEARCH_ENGINE_LIN_MORTON_QUERYPROCESSOR_H
