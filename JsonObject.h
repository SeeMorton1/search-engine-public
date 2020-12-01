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
    string title;
    string jsonFileName;
public:

    JsonObject();
    ~JsonObject();
    JsonObject(const JsonObject& copy);

    void addText(const string& t);
    void addAuthors(const string& author);
    void jsonFileNameSet(string json);
    void setTitle(const string& t);

    vector<string> returnText();
    vector<string> returnAuthor();
    string returnJsonFileName();


};


#endif //SEARCH_ENGINE_LIN_MORTON_JSONOBJECT_H
