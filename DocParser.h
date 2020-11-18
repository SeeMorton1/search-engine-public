//
// Created by zihao on 11/14/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#define SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

#include <dirent.h>
#include <cstdio>
#include "JsonObject.h"
using namespace rapidjson;
using namespace std;

class DocParser{
private:

    vector<JsonObject> vectorOfJson;
    string author;
    string text;
    string jsonfile;


public:

    DocParser();
    ~DocParser();
    DocParser(const DocParser& copy);

    int parseFiles(const char *file);
    void toLower();
    void removeStop();
    void removeStem();

    //Test Functions
    void printText();
    void printAuthor();
    void printjsonfile();



};
#endif //SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
