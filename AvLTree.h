//
// Created by Conner Morton on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
#define SEARCH_ENGINE_LIN_MORTON_AVLTREE_H


#include <iostream>
using namespace std;
template<typename T>
class AvLTree {
private:
    class AvLNode {
    private:
        T data;
        AvLNode *par;
        AvLNode *left;
        AvLNode *right;
        int height;
    public:
        AvLNode() {
            left = nullptr;
            right = nullptr;
            height = 0;
            par = nullptr;
        }

        AvLNode(T &in) {
            data = in;
            par = left = right = nullptr;
            height = 0;
        }

        void removeParent() {
            par = nullptr;
        }

        int updateHeight() {
            if (left == nullptr) {
                if (right == nullptr) {
                    height = 0;
                } else {
                    height = right->height + 1;
                }
            } else if (right == nullptr) {
                height = left->height + 1;
            } else if (left->height > right->height) {
                height = left->height + 1;
            } else {
                height = right->height + 1;
            }
            return height;
        }

        int getBal() {
            int result;
            if (left == nullptr) {
                if (right == nullptr) {
                    result = 0;
                } else {
                    result = -right->height - 1;
                }
            } else if (right == nullptr) {
                result = left->height + 1;
            } else {
                result = left->height - right->height;
            }
            return result;
        }

        T &getData() {
            return data;
        }

        int getHeight() {
            return height;
        }

        AvLNode *getLeft() {
            return left;
        }

        AvLNode *getRight() {
            return right;
        }

        AvLNode *getPar() {
            return par;
        }

        AvLNode *setLeft(AvLNode *in) {
            if (in != nullptr) {
                in->par = this;
            }
            left = in;
            updateHeight();
            return left;
        }

        AvLNode *setRight(AvLNode *in) {
            if (in != nullptr) {
                in->par = this;
            }
            right = in;
            updateHeight();
            return right;
        }

        T &setData(T &in) {
            data = in;
            return data;
        }

        int setHeight(int i) {
            height = i;
            return height;
        }

    };

private:
    AvLNode *root;
    long n;
private:
    void balanceNode(AvLNode *A) {

        int bal = A->getBal();
        if (bal > 1) {
            if (A->getLeft()->getBal() < 0)
                rotateLeft(A->getLeft());
            rotateRight(A);

        } else if (bal < -1) {
            if (A->getRight()->getBal() > 0)
                rotateRight(A->getRight());
            rotateLeft(A);
        }

    }

    void rotateLeft(AvLNode *A) {
        enum {
            left, right
        } side;
        AvLNode *par = A->getPar();
        if (par != nullptr && par->getLeft() == A) {
            side = left;
        } else {
            side = right;
        }

        AvLNode *t = A->getRight();
        A->setRight(t->getLeft());
        t->setLeft(A);

        if (par == nullptr) {
            setRoot(t);
        } else if (side == left) {
            par->setLeft(t);
        } else {
            par->setRight(t);
        }
    }

    void rotateRight(AvLNode *A) {
        enum {
            left, right
        } side;
        AvLNode *par = A->getPar();
        if (par != nullptr && par->getLeft() == A) {
            side = left;
        } else {
            side = right;
        }
        AvLNode *t = A->getLeft();
        A->setLeft(t->getRight());
        t->setRight(A);
        if (par == nullptr) {
            setRoot(t);
        } else if (side == left) {
            par->setLeft(t);
        } else {
            par->setRight(t);
        }
    }

    void setRoot(AvLNode *A) {
        root = A;
        if (root != nullptr) {
            root->removeParent();
        }
    }

    int space(int branch) {
        int spacer = 2;
        for (int i = 0; i < branch; i++) {
            spacer += 2;
        }
        return spacer;
    }


public:
    AvLTree<T>() {
        root = nullptr;
        n = 0;
    }

    AvLTree(T &in) {
        root = new AvLNode(in);
    }

    ~AvLTree<T>() {
        Clear(root);
        root = nullptr;
    }

    AvLTree(const AvLTree<T> &copy) {
        root = copySubTree(copy.root);
    }

    AvLTree<T> &operator=(const AvLTree<T> &copy) {
        root = copySubTree(copy.root);
        return *this;
    }

    AvLNode *copySubTree(AvLNode *curr) {
        AvLNode *newLeft, *newRight, *newPar;
        if (curr == nullptr) {
            return nullptr;
        }
        if (curr->getLeft() == nullptr) {
            newLeft = nullptr;
        } else {
            newLeft = copySubTree(curr->getLeft());
        }
        if (curr->getRight() == nullptr) {
            newRight = nullptr;
        } else {
            newRight = copySubTree(curr->getRight());
        }
        newPar->setRight(newRight);
        newPar->setData(curr->getData());
        newPar->setLeft(newLeft);
        newPar->setHeight(curr->getHeight());
        return newPar;
    }

    bool insert(T &in) {
        n++;
        if (root == nullptr) {
            root = new AvLNode(in);
        } else {
            AvLNode *toAdd = nullptr;
            AvLNode *curr = root;
            while (curr != nullptr && toAdd == nullptr) {
                if (in < curr->getData()) {
                    if (curr->getLeft() == nullptr) {
                        toAdd = curr->setLeft(new AvLNode(in));
                    } else {
                        curr = curr->getLeft();
                    }
                } else if (in > curr->getData()) {
                    if (curr->getRight() == nullptr) {
                        toAdd = curr->setRight(new AvLNode(in));
                    } else {
                        curr = curr->getRight();
                    }
                } else {
                    toAdd = curr;
                    return false;
                }
            }
            //iterate back through the AVL tree to get the height so just go parent to parent to get levels
            curr = toAdd;
            while (curr != nullptr) {

                curr->updateHeight();
                balanceNode(curr);
                curr = curr->getPar();
            }
        }
        return true;
    }

    bool isFound(T &in) {
        AvLNode *curr = root;
        while (curr != nullptr) {
            if (in == curr->getData()) {
                return true;
            } else if (in < curr->getData()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        return false;
    }

    AvLNode *search(T &in) {
        AvLNode *curr = root;
        while (curr != nullptr) {
            if (in == curr->getData()) {
                break;
            } else if (in < curr->getData()) {
                curr = curr->getLeft();
            } else {
                curr = curr->getRight();
            }
        }
        return curr;
    }

    void Clear() {
        clear(root);
        root = nullptr;
    }

    void Clear(AvLNode *in) {
        if (in == nullptr) {
            return;
        }
        Clear(in->getLeft());
        Clear(in->getRight());
        delete in;
    }

    AvLNode *getRoot() {
        return root;
    }
};


#endif //SEARCH_ENGINE_LIN_MORTON_AVLTREE_H
