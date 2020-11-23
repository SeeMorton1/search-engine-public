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
    int getHeight(AvLNode<T>* getH)const{
        if(getH == nullptr){
            return -1;
        }else{
            return getH->height;
        }
    }
    int max(int l,int r) const {
        return l>r?l:r;
    }

    void rotateLeftChild(AvLNode<T>*& A){
        AvLNode<T>* rA = A->right;
        A->right = rA->left;
        if(rA->left!=nullptr){
            rA->left->parent =A;
        }
        rA->parent = A->parent;
        if(A->parent== nullptr){
            this->root = rA;
        }else if(A==A->parent->left){
            A->parent->left = rA;
        }else{
            A->parent->right = rA;
        }

        rA->left = A;
        A->parent = rA;

        A->bal = A->bal-1-max(0,rA->bal);
        rA->bal = rA->bal-1+min(0,rA->bal);

    }

    void rotateRightChild(AvLNode<T>* A){
        AvLNode<T>* lA = A->left;
        A->left = lA->right;
        if(lA->right!= nullptr){
            lA->right->parent = A;
        }
        lA->parent = A->parent;
        if(A->parent == nullptr){
            this->root = lA;
        }else if(A==A->parent->right){
            A->parent->right = lA;
        }else{
            A->parent->left = lA;
        }
        lA->right = A;
        A->parent = lA;

        A->bal = A->bal +1 -min(0,lA->bal);
        lA->bal = lA->bal +1+max(0,A->bal);
    }
    void updateBalance(AvLNode<T>* A){
        if(A->bal<-1||A->bal >1){
           rebalance(A);
            return;
        }
        if(A->parent!= nullptr){
            if(A==A->parent->left){
                A->parent->bal -=1;
            }
            if(A==A->parent->right){
                A->parent->bal +=1;
            }
            if(A->parent->bal !=0){
                updateBalance(A->parent);
            }
        }
    }
    void rebalance(AvLNode<T>* A){
        if(A->bal>0){
            if(A->right->bal<0){
                rotateRightChild(A->right);
                rotateLeftChild(A);
            }else{
                rotateLeftChild(A);
            }
        }else if(A->bal<0){
            if(A->left->bf>0){
                rotateLeftChild(A->left);
                rotateRightChild(A);
            }
            else{
                rotateRightChild(A);
            }
        }
    }





//    void updatePathFactors(AvLNode<T> *curr, T &in);
//
//    void leftRotation(AvLNode<T> *A, T &in);
//
//    void rightRotation(AvLNode<T> *A, T &in);
//
//    void doubleLeftRotation(AvLNode<T> *A, T &in);
//
//    void doubleRightRotation(AvLNode<T> *A, T &in);


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
    AvLNode<T>* copySubTree(const AvLNode<T>* curr){
        AvLNode<T>* newLeft, *newRight, *newPar;
        if (curr== nullptr){
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
        newPar->bal = curr->bal;
        return newPar;
    }

    int numNodes() {
        int n;
        AvLNode<T> *curr = root;
        while (curr != nullptr) {
            n++;
            curr = curr->left;
        }
    }

    int getBalance(const AvLNode<T> *A) {
        if (A == nullptr) {
            return 0;
        }

        return getHeight(A->left) - getHeight(A->right);
    }

    void Clear();

    bool isFound(T &in);

    void insert(T& x){

        auto* A = new AvLNode<T>(x, nullptr, nullptr,0);
        A->parent = nullptr;
        AvLNode<T>* y = nullptr;
        AvLNode<T>* n = this->root;
        while(n!= nullptr){
            y=n;
            if(A->data<n->data){
                n=n->left;
            }else{
                n=n->right;
            }
        }
        A->parent = y;
        if(y== nullptr){
            root = A;
        }else if(A->data<y->data){
            y->left = A;
        }else{
            y->right = A;
        }


    }

    AvLNode<T> *search(AvLNode<T> *h, T &in);

    AvLNode<T>* remove(const AvLNode<T>* A,T &in);

    AvLNode<T>* getRoot(){
        return root;
    }

    AvLNode<T>* minNode(const AvLNode<T>* A){
        AvLNode<T>* curr = A;
        while(curr->left!= nullptr){
            curr = curr->left;
        }
        return curr;
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
AvLNode<T> *AvLTree<T>::search(AvLNode<T> *h, T &in) {
    if (h == nullptr) {
        std::cout << "Not Found from search" << std::endl;
        return nullptr;
    }
    T checker = h->data;
    if (checker == in) {
        return h;
    }
    if (checker > in) {
        return search(h->left, in);
    }
    if (checker < in) {
        return search(h->right, in);
    }
}



template<typename T>
AvLNode<T>* AvLTree<T>::remove(const AvLNode<T>* A, T &in) {
    if(A == nullptr){
        return A;
    }
    if(in<A->data){
        A->left=remove(A->left,in);
    }else if(in>A->data){
        A->right = remove(A->right,in);
    }

    else{
        if(A->left== nullptr||A->right== nullptr){
            AvLNode<T>* temp = A->left?A->left:A->right;
            if(temp== nullptr){
                temp = A;
                A = nullptr;
            }else{
                *A = temp;
                free(temp);
            }
        }else{
            AvLNode<T>* temp = minNode(A->right);
            A->data = temp->data;
            A->right = remove(A->right,temp->data);
        }
    }
    if(A==nullptr){
        return A;
    }
    A->height = max(getHeight(A->left),getHeight(A->right))+1;


    int bal = getHeight(A->left)-getHeight(A->right);
    if(bal>1&&(getBalance(A->left)>=0)){
        return rotateRightChild(A);
    }
    if(bal>1&&(getBalance(A->left)<0)){
        A->left = rotateLeftChild(A->left);
        return rotateRightChild(A);
    }
    if(bal<-1&&(getBalance(A->right)<=0)){
        return rotateLeftChild(A);
    }
    if(bal<-1&&(getBalance(A->right)>0)){
        A->right = rotateRightChild(A->right);
        return rotateLeftChild(A);
    }
    return A;
}


#endif //SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
