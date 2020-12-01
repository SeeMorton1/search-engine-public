//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>
#include "IndexNodesTest.h"
#include "DocParser.h"
#include "IndexProcessor.h"
#include "QueryProcessor.h"
#include "UserInterface.h"
using namespace std;
int main(int argc, char **argv) {
    cout << "#####Parsing Jsons#####" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";
    string qq = "AND virus covid not research";
    QueryProcessor quer;
    quer.setSearch(qq);

    quer.genQuery();


    string toFind = argv[1];
    // IndexNodesTest::runTests();
    const char *fileName = argv[2];

    //IndexNodesTest::runTests();

    ifstream file;
    file.open(argv[3]);
    DocParser docParser;

    docParser.parseFiles(argv[2], file); //1 is the path to the .json folder
    cout << "#####PROCESSING INDEX#####" << endl;
    //
    IndexProcessor p;
    p.createIndex(docParser);

    list<string> foundIDS = p.findWord(toFind);
    set<string> setOfFoundIDS;
    //list<string> foundIDS = p.findIDS(toFind,docParser);

    for (const auto &it:foundIDS) {
        setOfFoundIDS.insert(it);
    }
    vector<string> uniqueIds;
    for (const auto &it:setOfFoundIDS){
        uniqueIds.push_back(it);
    }
    UserInterface newInterface;
    newInterface.findObjects(uniqueIds,docParser.getJsons());
    cout << newInterface.returnArticlesIndexed() << endl;
    cout << newInterface.averageNumberOfWordsPerArticle() << endl;
    cout << newInterface.returnUniqueAuthorsNumber() << endl;
    //long n = p.getIndex().g




    file.close();



    cout << "Finished" << endl;
    output.close();
    return 0;
}
