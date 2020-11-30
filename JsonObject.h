//
// Created by zihao on 11/17/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_JSONOBJECT_H
#define SEARCH_ENGINE_LIN_MORTON_JSONOBJECT_H


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

class JsonObject {
private:
    vector<string> text;
    vector<string> authors;
    string jsonFileName;
    int wordCount;
public:

    JsonObject();
    ~JsonObject();
    JsonObject(const JsonObject& copy);

    void addText(const string& t);
    void addAuthors(const string& author);
    void jsonFileNameSet(string json);
    void setWordCount(int x);

    vector<string> returnText();
    vector<string> returnAuthor();
    string returnJsonFileName();
    int returnWordCount();


};


#endif //SEARCH_ENGINE_LIN_MORTON_JSONOBJECT_H
