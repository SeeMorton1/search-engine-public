//
// Created by Conner Morton on 11/14/2020.
//

#include <iostream>
#include <fstream>
#include "DocParser.h"
#include "IndexProcessor.h"
#include "HashTable.h"
#include "QueryProcessor.h"
using namespace std;
int main(int argc, char **argv) {
    cout << "#####Parsing Jsons#####" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";
    string qq = "AND virus covid not research";
    QueryProcessor quer;
    quer.setSearch(qq);

    quer.genQuery();

    HashTable<string,list<string>> table;

    string author = "Berkins";
    list<string> ids;
    ids.emplace_back("2");
    table.insert(author,ids);
    table[author].emplace_back("3");



    string toFind = argv[1];
    // IndexNodesTest::runTests();


    //IndexNodesTest::runTests();

    //Zihao's coding stuffs
    //Zihao's coding stuff
    ifstream file;
    file.open(argv[3]);
    DocParser docParser;

    docParser.parseFiles(argv[2], file); //1 is the path to the .json folder
    //docParser.printText();

    cout << "#####PROCESSING INDEX#####" << endl;
    //
    IndexProcessor p;
    p.createIndex(docParser);

    list<string> foundIDS = p.findWord(toFind);

    //list<string> foundIDS = p.findIDS(toFind,docParser);

    for (const auto &it:foundIDS) {
        cout << it << endl;

    }





    //file.close();



    cout << "Finished" << endl;
    output.close();
    return 0;
}
