//
// Created by Conner Morton on 11/27/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_QUERY_H
#define SEARCH_ENGINE_LIN_MORTON_QUERY_H

#include <iostream>
#include <string>

using namespace std;

class Query {
private:
    string in;
    string author;
    string andQ;
    string orQ;
    string notQ;
public:
    Query() = default;

    ~Query() = default;

    Query(const Query &copy) = default;


    void setAuthor(const string &auth);

    void setIn(const string &n);

    void setAndQ(const string &an);

    void setNot(const string &n);

    void setOr(const string &s);
};


#endif //SEARCH_ENGINE_LIN_MORTON_QUERY_H
