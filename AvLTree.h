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


    AvLNode<T> *searchUtil(AvLNode<T> *head, T x) {
        if (head == nullptr) return nullptr;
        T k = head->data;
        if (k == x) return head;
        if (k > x) return searchUtil(head->left, x);
        if (k < x) return searchUtil(head->right, x);
    }

private:

    int height(AvLNode<T> *head) {
        if (head == nullptr) return 0;
        return head->height;
    }

    AvLNode<T> *rightRotation(AvLNode<T> *head) {
        AvLNode<T> *newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    AvLNode<T> *leftRotation(AvLNode<T> *head) {
        AvLNode<T> *newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        newhead->height = 1 + max(height(newhead->left), height(newhead->right));
        return newhead;
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

    bool isFound(T &in);


    void remove(T &in);

    AvLNode<T>* getRoot(){
        return root;
    }

};

//template<typename T>
//void AvLTree<T>::updatePathFactors(AvLNode<T> *curr, T &in) {
//    while (curr != nullptr) {
//        if (in < curr->data) {
//            curr->bal++;
//            curr = curr->left;
//        } else if (in > curr->data) {
//            curr->bal--;
//            curr = curr->right;
//        } else {
//            break;
//        }
//    }
//}
//
//template<typename T>
//void AvLTree<T>::leftRotation(AvLNode<T> *A, T &in) {
//    AvLNode<T> *leftA = A->left;
//    AvLNode<T> *rightLeftA = leftA->right;
//    AvLNode<T> *leftLeftA = leftA->left;
//    AvLNode<T> *rightA = A->right;
//    A->left = leftLeftA;
//    A->right = leftA;
//    leftA->left = rightLeftA;
//    leftA->right = rightA;
//    std::swap(A->data, leftA->data);
//    std::swap(A, leftA);
//    A->bal = 0;
//    leftA->bal = 0;
//    updatePathFactors(leftA->left, in);
//}
//
//template<typename T>
//void AvLTree<T>::rightRotation(AvLNode<T> *A, T &in) {
//    AvLNode<T> *rightA = A->right;
//    AvLNode<T> *rightRightA = rightA->right;
//    AvLNode<T> *leftRightA = rightA->left;
//    AvLNode<T> *leftA = A->left;
//
//    A->left = leftRightA;
//    A->right = rightA;
//    rightA->left = leftA;
//    rightA->right = rightRightA;
//
//    std::swap(A->data, rightA->data);
//    std::swap(A, rightA);
//
//    A->bal = 0;
//    rightA->bal = 0;
//    updatePathFactors(rightA->right, in);
//}
////TODO: Rewrite double left rotation to make it simpler to read.
//template<typename T>
//void AvLTree<T>::doubleLeftRotation(AvLNode<T> *A, T &in) {
//
//    AvLNode<T> *leftA = A->left;
//    AvLNode<T> *rightLeftA = leftA->right;
//    AvLNode<T> *rightA = A->right;
//    AvLNode<T> *leftRightLeftA = rightLeftA->left;
//    AvLNode<T> *rightRightLeftA = rightLeftA->right;
//
//    updatePathFactors(rightLeftA, in);
//    int bal = rightLeftA->bal;
//    A->right = rightLeftA;
//    leftA->right = leftRightLeftA;
//    rightLeftA->left = rightRightLeftA;
//    rightLeftA->right = rightA;
//    std::swap(A->data, rightLeftA->data);
//    std::swap(A, rightLeftA);
//
//    rightLeftA->bal = 0;
//    if (bal == 0) {
//        leftA->bal = 0;
//        A->bal = 0;
//    } else if (bal == 1) {
//        leftA->bal = 0;
//        A->bal = -1;
//    } else if (bal == -1) {
//        leftA->bal = 1;
//        A->bal = 0;
//    }
//}
//
//template<typename T>
//void AvLTree<T>::doubleRightRotation(AvLNode<T> *A, T &in) {
//    //RE WRITING TO MAKE EASIER TO READ
//    AvLNode<T> *B = A->right, *C = B->left;
//    AvLNode<T> *lA = A->left, *lC = C->left, *rC = C->right;
//
//    updatePathFactors(C, in);
//    int b = C->bal;
//
//    A->left = C;
//    B->left = rC;
//    C->left = lA;
//    C->right = lC;
//
//    std::swap(A->data, C->data);
//    std::swap(A, C);
//
//
//    C->bal = 0;
//
//    if (b == 0) {
//        A->bal = 0;
//        B->bal = 0;
//    } else if (b == 1) {
//        A->bal = 0;
//        B->bal = -1;
//    } else if (b == -1) {
//        A->bal = 1;
//        B->bal = 0;
//    }
//
//
////    AvLNode<T> *rightA = A->right;
////    AvLNode<T> *leftRightA = rightA->left;
////    AvLNode<T> *leftA = A->left;
////    AvLNode<T> *leftLeftRightA = leftRightA->left;
////    AvLNode<T> *rightLeftRightA = leftRightA->right;
////    updatePathFactors(leftRightA, in);
////    int bal = leftRightA->bal;
////    A->left = leftRightA;
////    rightA->left = rightLeftRightA;
////    leftRightA->left = leftA;
////    leftRightA->right = leftLeftRightA;
////
////    std::swap(A->data, leftRightA->data);
////    std::swap(A, leftRightA);
////
////    leftRightA->bal = 0;
////
////    if (bal == 0) {
////        A->bal = 0;
////        rightA->bal = 0;
////    } else if (bal == 1) {
////        A->bal = 0;
////        rightA->bal = -1;
////    } else if (bal == -1) {
////        A->bal = 1;
////        rightA->bal = 0;
////    }
//}
//
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

//template<typename T>
//void AvLTree<T>::insert(T &in) {
//    AvLNode<T> *curr = root;
//    AvLNode<T> *back = nullptr;
//    AvLNode<T> *last = nullptr;
//
//    while (curr != nullptr) {
//        back = curr;
//        if (curr->bal != 0) {
//            last = curr;
//        }
//        if (in < curr->data) {
//            curr = curr->left;
//        } else if (in > curr->data) {
//            curr = curr->right;
//        } else {
//            return;
//        }
//    }
//    AvLNode<T> *n = new AvLNode<T>(in, nullptr, nullptr,0);
//    if (root != nullptr) {
//        if (in < back->data) {
//            back->left = n;
//        } else {
//            back->right = n;
//        }
//    } else {
//        root = n;
//    }
//
//    if (last == nullptr) {
//        updatePathFactors(root, in);
//        return;
//    }
//    if (last->bal == 1) {
//        if (in < last->data) {
//            if ((last->left)->data > in) {
//                leftRotation(last, in);
//            } else {
//                doubleLeftRotation(last, in);
//            }
//        } else {
//            updatePathFactors(last, in);
//        }
//
//    } else if (last->bal == -1) {
//        if (in > last->data) {
//            if ((last->right)->data < in) {
//                rightRotation(last, in);
//            } else {
//                doubleRightRotation(last, in);
//            }
//        } else {
//            updatePathFactors(last, in);
//        }
//    }
//
//}
//
//template<typename T>
//AvLNode<T> *AvLTree<T>::search(AvLNode<T> *h, T &in) {
//    if (h == nullptr) {
//        std::cout << "Not Found from search" << std::endl;
//        return nullptr;
//    }
//    T checker = h->data;
//    if (checker == in) {
//        return h;
//    }
//    if (checker > in) {
//        return search(h->left, in);
//    }
//    if (checker < in) {
//        return search(h->right, in);
//    }



#endif //SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
