//
// Created by Conner Morton on 11/15/2020.
//
#include "AvLTree.h"
#include "IndexNodesTest.h"
#include "Index.h"
#include "HashTable.h"
//
// Created by Conner Morton on 11/15/2020.
//
void IndexNodesTest::runTests() {
    vector<IndexNode *> nodes;
    string term1 = "covid-19";
    string term2 = "research";
    string term3 = "infection";
    Index index1;
    Index index2;

    index1.setWord(term1);
    index2.setWord(term2);

    index1.setCount(4);
    index2.setCount(2);


    AvLTree<Index> testTree;
    testTree.insert(index1);
    testTree.insert(index2);

    Index index3;
    index3.setWord(term3);

    index3.setCount(7);
    testTree.insert(index3);

    HashTable hash;
    hash.insertItem("Zihao Lin", "Page 1");
    hash.insertItem("Zihao Lin", "Page 2");


    cout << "Tests ran" << std::endl;


}
