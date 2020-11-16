//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>

#include "DocParser.h"

using namespace std;
int main(int argc, char **argv) {
    cout << "Hi zihao gladd you downloaded" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";


    DocParser docParser;
    docParser.parseFiles(argv[1]);
    output.close();
    return 0;
}
