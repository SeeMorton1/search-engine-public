//
// Created by Conner Morton on 11/16/2020.
//

#include "Index.h"

Index::Index() {
    count = 0;
}

Index::Index(const Index &copy) {
    count = copy.count;
    word = copy.word;
    for (const auto &it:copy.IDs) {
        IDs.push_back(it);
    }
}

Index &Index::operator=(const Index &copy) {
    IDs.clear();


    for (const auto &it:copy.IDs) {

        IDs.push_back(it);
    }
    count = copy.count;
    word = copy.word;


    return *this;
}

Index::~Index() = default;

void Index::addID(const string &id) {
    IDs.push_back(id);
    addCount();
}

void Index::setWord(const string &in) {
    word = in;
}

void Index::addCount() {
    count++;
}

bool Index::operator==(const Index &c) {
    return word == c.word;
}

bool Index::operator<(const Index &c) {
    return word < c.word;
}

bool Index::operator>(const Index &c) {
    return word > c.word;
}

//Index &Index::createIndex(string &w,const DocParser& doc ) {
//
//
//    return <#initializer#>;
//}



