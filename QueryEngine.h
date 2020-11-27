//
// Created by Zihao Lin on 11/25/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_QUERYENGINE_H
#define SEARCH_ENGINE_LIN_MORTON_QUERYENGINE_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "set"
#include "JsonObject.h"
using namespace std;

class QueryEngine
{
  public:
    int numberOfWords;
    string ANDwords;
    string ORwords;
    string NOTwords;

    vector<JsonObject> FileContainer;
    set<JsonObject> uniqueFileContainer;


  private:
    QueryEngine();
    QueryEngine(QueryEngine& copy);
    ~QueryEngine();

    void queryHandler(string query); //Reads in query from UI
    void setNumberOfWords(); //Counts number of words that are not AND OR NOT.

    void removeNotFiles(); //Goes through File Container and removes the Not Files
    void findAndFiles(); //Goes through the file to see if there are duplicates
    void removeDupes(); //Remove Duplicate Files




};

#endif // SEARCH_ENGINE_LIN_MORTON_QUERYENGINE_H
