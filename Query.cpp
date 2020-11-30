//
// Created by Conner Morton on 11/27/2020.
//

#include "Query.h"

void Query::setAndQ(const string &an) {
    andQ = an;
}

void Query::setAuthor(const string &auth) {
    author = auth;
}

void Query::setIn(const string &n) {
    in = n;
}

void Query::setNot(const string &n) {
    notQ = n;
}

void Query::setOr(const string &s) {
    orQ = s;
}
