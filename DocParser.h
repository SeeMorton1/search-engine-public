//
// Created by zihao on 11/14/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#define SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/ostreamwrapper.h"
#include <dirent.h>
using namespace rapidjson;
using namespace std;

class DocParser{
private:
    string author;
    string text;
    ifstream file;


public:

    int parseFiles(const char *file);
    void removeStop();
    void removeStem();

};
#endif //SEARCH_ENGINE_LIN_MORTON_DOCPARSER_H
