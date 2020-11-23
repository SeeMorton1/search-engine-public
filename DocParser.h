//
// Created by zihao on 11/14/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#define SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "porter2_stemmer.h"

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include <dirent.h>
#include <cstdio>
#include "JsonObject.h"
#include "AvLTree.h"
#include<bits/stdc++.h>

using namespace rapidjson;
using namespace std;

class DocParser{
private:

    vector<JsonObject> vectorOfJson;
    AvLTree<string> stopWords;
    string author;
    string text;
    string jsonfile;


public:
    DocParser();
    ~DocParser();
    DocParser(const DocParser& copy);

    int parseFiles(const char *file, ifstream& stopWords);
    void readInStopWords(ifstream& stopWords);
    void removeStop();

    vector<JsonObject> getJsons();

    //Test Functions
    void printText();
    void printAuthor();
    void printjsonfile();



};
#endif //SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
