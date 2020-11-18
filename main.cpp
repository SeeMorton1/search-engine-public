//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>
#include "IndexNodesTest.h"
#include "DocParser.h"

using namespace std;
int main(int argc, char **argv) {
    cout << "Hi zihao gladd you downloaded" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";



//    DocParser docParser;
//    docParser.parseFiles(argv[1]); //1 is the path to the .json folder

   // IndexNodesTest::runTests();
   //Comment these out Conner or else it will print a lot of stuff
    DocParser docParser;
    docParser.parseFiles(argv[1]); //1 is the path to the .json folder
    docParser.printAuthor();
    docParser.printText();
    docParser.printjsonfile();

    cout << "Finished" << endl;
    output.close();
    return 0;
}
