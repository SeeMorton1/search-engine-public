//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>
#include "IndexNodesTest.h"
#include "DocParser.h"
#include "IndexProcessor.h"
using namespace std;
int main(int argc, char **argv) {
    cout << "#####Parsing Jsons#####" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";





    // IndexNodesTest::runTests();


    //IndexNodesTest::runTests();

    //Zihao's coding stuffs
    //Zihao's coding stuff
    ifstream file;
    file.open("stopWords.txt");
    DocParser docParser;
    docParser.parseFiles(argv[1], file); //1 is the path to the .json folder
    docParser.printText();

    cout << "#####PROCESSING INDEX#####" << endl;
    //
//    IndexProcessor p;
//    p.createIndex(docParser);
//    list<string> ID = p.findWord("virus");

//    for (auto it:ID) {
//        cout << it << endl;
//    }




    //file.close();



    cout << "Finished" << endl;
    output.close();
    return 0;
}
