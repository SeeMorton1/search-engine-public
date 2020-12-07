//
// Created by Zihao Lin on 11/25/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_USERINTERFACE_H
#define SEARCH_ENGINE_LIN_MORTON_USERINTERFACE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "JsonObject.h"
#include "vector"
#include "IndexProcessor.h"
#include "DocParser.h"
#include "Query.h"
#include "DocParser.h"
#include "SearchEngine.h"
#include "QueryProcessor.h"
using namespace std;

class UserInterface
{
  private:
    vector<string> queryWords;
    vector<JsonObject> topRankedArticles;
    vector<int> countVector;
    vector<JsonObject> SearchResults;
    vector<JsonObject> VectorOfJsons;
    set<string> Authors;
    IndexProcessor p;
    long numberOfIndex;
    long numberOfWords;
    long sizeOfNode;

    string query;
  public:
    void startUI(const char *file, ifstream& stopWords, ifstream& csvFile); //Overall User Interface
    void clearIndex(); //Cleans Index
    void printArticle(string id,const char *file); //300 Words of article
    vector<string> createUniqueIds(list<string> list); //Changes into Set
    void printStats(); //Prints object info
    void printStatsUnsorted(); //^^^
    void addAuthors(DocParser parse); //Add authors
    void processIndex(const char* file,const char* csv,const char* stop);
    void setCount(long Nodes); //Count for rankings
    void printTop50(); //Top 50
    void buildJsons();
    JsonObject findFile(string ID, const char *file,ifstream &stop, ifstream &csv); //Finds file given ID
    void populateTopFiles(); //Rankings


    //Statistical Things
    void findObjects(vector<string> jsonIDS, const char* file, ifstream& stop, ifstream& csv);
    void findObjects(vector<string> jsonIDS,vector<JsonObject> allFiles);
    long returnArticlesIndexed();
    long averageNumberOfWordsPerArticle();
    long returnUniqueWordsNumber(); //Number of Nodes in avl
    int returnUniqueAuthorsNumber();
    vector<string> returnMostCommonWords();

};

#endif // SEARCH_ENGINE_LIN_MORTON_USERINTERFACE_H
