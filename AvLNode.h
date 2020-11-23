//
// Created by Conner Morton on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_AVLNODE_H
#define SEARCH_ENGINE_LIN_MORTON_AVLNODE_H

template<typename T>
class AvLTree;


template<typename T>
class AvLNode {
    friend class AvLTree<T>;

public:


    AvLNode(const T& in, AvLNode* l,AvLNode* r,int h):data(in),left(l),right(r),bal(h){}



    T& getData(){return data;}


private:
    T data;
    AvLNode *left;
    AvLNode *parent;
    AvLNode *right;
    int bal;
};

#endif //SEARCH_ENGINE_LIN_MORTON_AVLNODE_H
