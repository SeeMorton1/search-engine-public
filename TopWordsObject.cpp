//
// Created by zihao on 12/3/2020.
//

#include "TopWordsObject.h"

TopWordsObject::TopWordsObject() = default;
TopWordsObject::~TopWordsObject() = default;
TopWordsObject::TopWordsObject(const TopWordsObject &copy) {
    word = copy.word;
    count = copy.count;
}

void TopWordsObject::setCount(int c) {
    count = c;
}
void TopWordsObject::setWord(string w) {
    word = w;
}
string TopWordsObject::returnWord() {
    return word;
}
int TopWordsObject::returnCount() {
    return count;
}