//
// Created by Conner Morton on 11/14/2020.
//

#include "IndexNode.h"

#include <utility>

IndexNode::IndexNode() {
    term = "";
    count = 0;
    height = 0;
    left = nullptr;
    right = nullptr;
}
void IndexNode::setRoot(IndexNode* roo) {
    root = roo;
}
void IndexNode::setLeft(IndexNode* l) {
    left = l;
}

void IndexNode::setRight(IndexNode* r) {
    right = r;
}

void IndexNode::setTerm(string s) {
    term = std::move(s);
}

void IndexNode::setCount(int c) {
    count = c;
}

void IndexNode::setHeight(int h) {
    height = h;
}

void IndexNode::findHeight() {
    IndexNode *curr = this;
    while (curr != nullptr) {
        height++;
        curr = curr->left;
    }
}

int IndexNode::getCount() const {
    return count;
}


