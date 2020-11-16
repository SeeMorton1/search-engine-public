//
// Created by Conner Morton on 11/15/2020.
//

#include "IndexNodesTest.h"
//
// Created by Conner Morton on 11/15/2020.
//
void IndexNodesTest::runTests() {
    vector<IndexNode*> nodes;
    string term1 = "covid-19";
    string term2 = "research";
    string term3 = "infection";
    auto *node1= new IndexNode;
    auto *node2=new IndexNode;
    auto *node3=new IndexNode;
    node1->setTerm(term1);node1->setCount(4);
    node2->setTerm(term2);node2->setCount(2);
    node3->setTerm(term3);node3->setCount(7);
    node1->setRight(node2);
    node1->setLeft(node3);
    node2->setRoot(node1);
    node3->setRoot(node1);
    nodes.emplace_back(node1);
    nodes.emplace_back(node2);
    nodes.emplace_back(node3);
    for(auto& it:nodes){
        cout<<it->getTerm()<<"["<<it->getCount()<<"]\n";
    }
}
