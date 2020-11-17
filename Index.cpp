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
    count = copy.count;
    word = copy.word;
    for (const auto &it:copy.IDs) {
        IDs.push_back(it);
    }
    return *this;
}

Index::~Index() = default;

void Index::addID(int id) {
    IDs.push_back(id);
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



