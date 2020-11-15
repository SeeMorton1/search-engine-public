//
// Created by Conner Morton on 11/14/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_INDEXNODE_H
#define SEARCH_ENGINE_LIN_MORTON_INDEXNODE_H

#include <iostream>
#include <list>

using namespace std;

class IndexNode {
public:
    IndexNode();

    string getTerm();

    int getCount();

    int getLeft();

    int getRight();

private:
    string term;
    int count;
    IndexNode *left;
    IndexNode *right;
    int height;
    list<int> IDs;
};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXNODE_H
