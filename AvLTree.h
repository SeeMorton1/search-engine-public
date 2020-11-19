//
// Created by Conner Morton on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
#define SEARCH_ENGINE_LIN_MORTON_AVLTREE_H

#include "AvLNode.h"
#include <iostream>

template<typename T>
class AvLTree {
private:
    AvLNode<T> *root;

    void updatePathFactors(AvLNode<T> *curr, T &in);

    void leftRotation(AvLNode<T> *A, T &in);

    void rightRotation(AvLNode<T> *A, T &in);

    void doubleLeftRotation(AvLNode<T> *A, T &in);

    void doubleRightRotation(AvLNode<T> *A, T &in);


    void Clear(AvLNode<T> *n);

public:
    AvLTree() {
        root = nullptr;
    }

    ~AvLTree() {
        Clear(root);
        root = nullptr;
    }

    void Clear();

    bool isFound(T &in);

    void insert(T &in);

    void remove(T &in);

};

template<typename T>
void AvLTree<T>::updatePathFactors(AvLNode<T> *curr, T &in) {
    while (curr != nullptr) {
        if (in < curr->data) {
            curr->bal++;
            curr = curr->left;
        } else if (in > curr->data) {
            curr->bal--;
            curr = curr->right;
        } else {
            break;
        }
    }
}

template<typename T>
void AvLTree<T>::leftRotation(AvLNode<T> *A, T &in) {
    AvLNode<T> *leftA = A->left;
    AvLNode<T> *rightLeftA = leftA->right;
    AvLNode<T> *leftLeftA = leftA->left;
    AvLNode<T> *rightA = A->right;
    A->left = leftLeftA;
    A->right = leftA;
    leftA->left = rightLeftA;
    leftA->right = rightA;
    std::swap(A->data, leftA->data);
    std::swap(A, leftA);
    A->bal = 0;
    leftA->bal = 0;
    updatePathFactors(leftA->left, in);
}

template<typename T>
void AvLTree<T>::rightRotation(AvLNode<T> *A, T &in) {
    AvLNode<T> *rightA = A->right;
    AvLNode<T> *rightRightA = rightA->right;
    AvLNode<T> *leftRightA = rightA->left;
    AvLNode<T> *leftA = A->left;

    A->left = leftRightA;
    A->right = rightA;
    rightA->left = leftA;
    rightA->right = rightRightA;

    std::swap(A->data, rightA->data);
    std::swap(A, rightA);

    A->bal = 0;
    rightA->bal = 0;
    updatePathFactors(rightA->right, in);
}
//TODO: Rewrite double left rotation to make it simpler to read.
template<typename T>
void AvLTree<T>::doubleLeftRotation(AvLNode<T> *A, T &in) {

    AvLNode<T> *leftA = A->left;
    AvLNode<T> *rightLeftA = leftA->right;
    AvLNode<T> *rightA = A->right;
    AvLNode<T> *leftRightLeftA = rightLeftA->left;
    AvLNode<T> *rightRightLeftA = rightLeftA->right;

    updatePathFactors(rightLeftA, in);
    int bal = rightLeftA->bal;
    A->right = rightLeftA;
    leftA->right = leftRightLeftA;
    rightLeftA->left = rightRightLeftA;
    rightLeftA->right = rightA;
    std::swap(A->data, rightLeftA->data);
    std::swap(A, rightLeftA);

    rightLeftA->bal = 0;
    if (bal == 0) {
        leftA->bal = 0;
        A->bal = 0;
    } else if (bal == 1) {
        leftA->bal = 0;
        A->bal = -1;
    } else if (bal == -1) {
        leftA->bal = 1;
        A->bal = 0;
    }
}

template<typename T>
void AvLTree<T>::doubleRightRotation(AvLNode<T> *A, T &in) {
    //RE WRITING TO MAKE EASIER TO READ
    AvLNode<T> *B = A->right;
    AvLNode<T> *c = B->left;
    AvLNode<T> *lA = A->left;
    AvLNode<T> *lC = c->left;
    AvLNode<T> *rC = c->right;

    updatePathFactors(c, in);
    int b = c->bal;

    A->left = c;
    B->left = rC;
    c->left = lA;
    c->right = lC;

    std::swap(A->data, c->data);
    std::swap(A, c);


    c->bal = 0;

    if (b == 0) {
        A->bal = 0;
        B->bal = 0;
    } else if (b == 1) {
        A->bal = 0;
        B->bal = -1;
    } else if (b == -1) {
        A->bal = 1;
        B->bal = 0;
    }


//    AvLNode<T> *rightA = A->right;
//    AvLNode<T> *leftRightA = rightA->left;
//    AvLNode<T> *leftA = A->left;
//    AvLNode<T> *leftLeftRightA = leftRightA->left;
//    AvLNode<T> *rightLeftRightA = leftRightA->right;
//    updatePathFactors(leftRightA, in);
//    int bal = leftRightA->bal;
//    A->left = leftRightA;
//    rightA->left = rightLeftRightA;
//    leftRightA->left = leftA;
//    leftRightA->right = leftLeftRightA;
//
//    std::swap(A->data, leftRightA->data);
//    std::swap(A, leftRightA);
//
//    leftRightA->bal = 0;
//
//    if (bal == 0) {
//        A->bal = 0;
//        rightA->bal = 0;
//    } else if (bal == 1) {
//        A->bal = 0;
//        rightA->bal = -1;
//    } else if (bal == -1) {
//        A->bal = 1;
//        rightA->bal = 0;
//    }
}

template<typename T>
void AvLTree<T>::Clear(AvLNode<T> *n) {
    if (n == nullptr) {
        return;
    }
    Clear(n->left);
    Clear(n->right);
    delete n;
}

template<typename T>
void AvLTree<T>::Clear() {
    clear(root);
    root = nullptr;
}

template<typename T>
bool AvLTree<T>::isFound(T &in) {
    AvLNode<T> *curr = root;
    while (curr != nullptr) {
        if (in < curr->data) {
            curr = curr->left;
        } else if (in > curr->data) {
            curr = curr->right;
        } else {
            return true;
        }
    }
    return false;
}

template<typename T>
void AvLTree<T>::insert(T &in) {
    AvLNode<T> *curr = root;
    AvLNode<T> *back = nullptr;
    AvLNode<T> *last = nullptr;

    while (curr != nullptr) {
        back = curr;
        if (curr->bal != 0) {
            last = curr;
        }
        if (in < curr->data) {
            curr = curr->left;
        } else if (in > curr->data) {
            curr = curr->right;
        } else {
            return;
        }
    }
    AvLNode<T> *n = new AvLNode<T>(in);
    if (root != nullptr) {
        if (in < back->data) {
            back->left = n;
        } else {
            back->right = n;
        }
    } else {
        root = n;
    }

    if (last == nullptr) {
        updatePathFactors(root, in);
        return;
    }
    if (last->bal == 1) {
        if (in < last->data) {
            if ((last->left)->data > in) {
                leftRotation(last, in);
            } else {
                doubleLeftRotation(last, in);
            }
        } else {
            updatePathFactors(last, in);
        }

    } else if (last->bal == -1) {
        if (in > last->data) {
            if ((last->right)->data < in) {
                rightRotation(last, in);
            } else {
                doubleRightRotation(last, in);
            }
        } else {
            updatePathFactors(last, in);
        }
    }
}


#endif //SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
