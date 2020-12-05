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

bool Query::hasAuthor() {
    return !author.empty();
}

bool Query::hasAnd() {
    return !andQ.empty();
}

bool Query::hasOr() {
    return !orQ.empty();
}

bool Query::hasNot() {
    return !notQ.empty();
}

Query &Query::operator=(const Query &copy) =default;

