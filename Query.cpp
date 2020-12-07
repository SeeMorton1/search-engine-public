//
// Created by Conner Morton on 11/27/2020.
//

#include "Query.h"

void Query::setAndQ(basic_string<char> an) {
    Porter2Stemmer::stem(an);
    andQ = an;
}

void Query::setAuthor(const string &auth) {
    author = auth;
}

void Query::setIn(basic_string<char> n) {
    Porter2Stemmer::stem(n);
    in = n;
}

void Query::setNot(basic_string<char> n) {
    Porter2Stemmer::stem(n);
    notQ = n;
}

void Query::setOr(basic_string<char> s) {
    Porter2Stemmer::stem(s);
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

