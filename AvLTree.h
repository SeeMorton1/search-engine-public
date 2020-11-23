//
// Created by Conner Morton on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
#define SEARCH_ENGINE_LIN_MORTON_AVLTREE_H

#include "AvLNode.h"
#include <iostream>
using namespace std;
template<typename T>
class AvLTree {
public:
    int n;
    AvLNode<T> *root;

    void insert(T x) {
        root = insertUtil(root, x);
    }


    AvLNode<T> *searchAlgo(AvLNode<T> *head, T x) {
        if (head == nullptr) return nullptr;
        T k = head->data;
        if (k == x) return head;
        if (k > x) return searchAlgo(head->left, x);
        if (k < x) return searchAlgo(head->right, x);
    }

private:

    int height(AvLNode<T> *head) {
        if (head == nullptr) return 0;
        return head->height;
    }

    AvLNode<T> *rightRotation(AvLNode<T> *head) {
        AvLNode<T> *m = head->left;
        head->left = m->right;
        m->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        m->height = 1 + max(height(m->left), height(m->right));
        return m;
    }

    AvLNode<T> *leftRotation(AvLNode<T> *head) {
        AvLNode<T> *m = head->right;
        head->right = m->left;
        m->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        m->height = 1 + max(height(m->left), height(m->right));
        return m;
    }

    AvLNode<T> *insertUtil(AvLNode<T> *head, T x) {
        if (head == nullptr) {
            n += 1;
            AvLNode<T> *temp = new AvLNode<T>(x);
            return temp;
        }
        if (x < head->data) head->left = insertUtil(head->left, x);

        else if (x > head->data) head->right = insertUtil(head->right, x);


        head->height = 1 + max(height(head->left), height(head->right));

        int bal = height(head->left) - height(head->right);

        if (bal > 1) {
            if (x < head->left->data) {
                return rightRotation(head);
            } else {
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        } else if (bal < -1) {
            if (x > head->right->data) {
                return leftRotation(head);
            } else {
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }


    void Clear(AvLNode<T> *n);

public:
    AvLTree<T>() {
        root = nullptr;
    }

    ~AvLTree<T>() {
        Clear(root);
        root = nullptr;
    }
    AvLTree(const AvLTree<T>& copy){
        root = copySubTree(copy.root);
    }
    AvLTree<T>&operator=(const AvLTree<T>& copy){
        root = copySubTree(copy.root);
        return *this;
    }
    AvLNode<T>* copySubTree(const AvLNode<T>* curr) {
        AvLNode<T> *newLeft, *newRight, *newPar;
        if (curr == nullptr) {
            return nullptr;
        }
        if (curr->left == nullptr) {
            newLeft = nullptr;
        } else {
            newLeft = copySubTree(curr->left);
        }
        if (curr->right == nullptr) {
            newRight = nullptr;
        } else {
            newRight = copySubTree(curr->right);
        }

        newPar->right = newRight;
        newPar->data = curr->data;
        newPar->left = newLeft;
        newPar->height = curr->height;
        return newPar;
    }

    void Clear();

    bool isFound(AvLNode<T> *curr, T &in);


    void remove(T &in);

    AvLNode<T>* getRoot(){
        return root;
    }

};
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
bool AvLTree<T>::isFound(AvLNode<T> *curr, T &in) {

    if (curr == nullptr) {
        return false;
    }
    if (curr->data == in) {
        return true;

    }
    if (in < curr->data) {
        return isFound(curr->left, in);
    } else {
        return isFound(curr->right, in);
    }
}

#endif //SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
