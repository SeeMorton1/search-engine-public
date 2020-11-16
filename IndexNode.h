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
//GETTERS


    string getTerm() { return term; };

    int getCount() const;

    IndexNode *getLeft() { return left; };

    IndexNode *getRight() { return right; };

    int getHeight();

//SETTERS
    void setRoot(IndexNode* roo);

    void setLeft(IndexNode* l);

    void setRight(IndexNode* r);

    void setTerm(string s);

    void setCount(int count);

    void setHeight(int height);

//FUNCTIONS
    void findHeight();

    void incrementCount() { count++; }

private:
    string term;
    int count;
    IndexNode *root;
    IndexNode *left;
    IndexNode *right;
    int height;
    list<int> IDs;
};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXNODE_H
