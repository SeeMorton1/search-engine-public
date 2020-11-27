//
// Created by Conner Morton on 11/26/2020.
//
//https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/



#include "QueryProcessor.h"

vector<string> tokenString(const string &str) {
    vector<string> words;
    stringstream ss(str);
    string buff;
    while (getline(ss, buff, ' ')) {
        transform(buff.begin(), buff.end(), buff.begin(), ::tolower);
        words.push_back(buff);
    }
    return words;
}

Query &QueryProcessor::genQuery() {
    Query q;
    string i = search;
    vector<string> words = tokenString(i);

}

