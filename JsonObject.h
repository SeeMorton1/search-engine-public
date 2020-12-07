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
    string publishTime;
    string publisher;
    int count;
public:

    JsonObject();
    ~JsonObject();
    JsonObject(const JsonObject& copy);

    void addText(const string& t);
    void addAuthors(const string& author);
    void jsonFileNameSet(string json);
    void setTitle(const string& t);
    void setPublisher(const string& p);
    void setPublishTime(const string& t);
    void startCount();
    void increaseCount();

    vector<string> returnText();
    vector<string> returnAuthor();
    string returnJsonFileName();
    string returnTitle();
    string returnTime();
    string returnPublisher();
    int returnCount();


};


#endif //SEARCH_ENGINE_LIN_MORTON_JSONOBJECT_H
