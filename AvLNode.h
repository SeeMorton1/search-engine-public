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
    AvLNode() {
        left = nullptr;
        right = nullptr;
        bal = 0;
    }

    AvLNode(T in) {
        left = nullptr;
        right = nullptr;
        bal = 0; //System for determining how balanced a node is.
        data = in;
    }
    T& getData(){return data;}


private:
    T data;
    int bal;
    AvLNode *left;
    AvLNode *right;
    AvLNode *root;
};

#endif //SEARCH_ENGINE_LIN_MORTON_AVLNODE_H
