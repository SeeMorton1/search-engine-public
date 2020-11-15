//
// Created by Conner Morton on 11/14/2020.
//
#include <iostream>
#include <fstream>
using namespace std;
int main() {
    cout << "Hi zihao gladd you downloaded" << endl;
    std::ofstream output("output.txt");
    output << "wrote to file";


    output.close();
    return 0;
}
