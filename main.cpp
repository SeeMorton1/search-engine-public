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
    ifstream file;
    file.open("stopWords.txt");
    DocParser docParser;
    docParser.parseFiles(argv[1],file); //1 is the path to the .json folder
    //docParser.removeStem();
//    docParser.printAuthor();
//    docParser.printText();
//    docParser.printjsonfile();
    cout<<"#####PROCESSING INDEX#####"<<endl;
    //
    IndexProcessor p;
    p.createIndex(docParser);

    //file.close();



    cout << "Finished" << endl;
    output.close();
    return 0;
}
