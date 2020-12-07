//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>
#include "DocParser.h"
#include "IndexProcessor.h"
#include "QueryProcessor.h"
#include "UserInterface.h"

using namespace std;

int main(int argc, char **argv) {
    /*
     * 1 - Word to Search
     * 2 - Direct Path to file
     * 3 - Direct Path to stopword
     * 4 - Direct Path to csv file
     */
    ifstream file;
    file.open(argv[3]);
    ifstream csv;
    csv.open(argv[4]);

    UserInterface newInterface;
    newInterface.startUI(argv[2], file, csv);

    file.close();
    csv.close();

    cout << "Finished" << endl;

    return 0;
}
