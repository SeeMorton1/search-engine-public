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
#include "TopWordsObject.h"
#include "DocParser.h"
#include "SearchEngine.h"

using namespace std;

class UserInterface
{
  private:
    vector<JsonObject> topRankedArticles;
    vector<JsonObject> SearchResults;
    vector<JsonObject> VectorOfJsons;
    vector<TopWordsObject> top50Words;
    vector<string> Authors;
    long numberOfIndex;
    long numberOfWords;
    long sizeOfNode;

    string query;
  public:
    void startUI(const char *file, ifstream& stopWords, ifstream& csvFile); //Overall User Interface
    void clearIndex(); //Cleans Index
    void printArticle(int x); //300 Words of article
    vector<string> createUniqueIds(list<string> list);
    void printStats();
    void addAuthors();

    void setCount(long Nodes);
    void printTop50();


    //Statistical Things
    void findObjects(vector<string> jsonIDS, vector<JsonObject> allFiles);
    long returnArticlesIndexed();
    long averageNumberOfWordsPerArticle();
    long returnUniqueWordsNumber(); //Number of Nodes in avl
    int returnUniqueAuthorsNumber();

};

/*
1. Write index - writes the current Index(AVL TRee and HAsh table) in the program to the CSV
2. Create Index - parses all of the documents and generates the Index (AVL tree and hash table).
2. Open file - Opens the CSV for quick access to the AVL tree
3. Clear index - Clear CSV File
4. search - Obvious
5. print stats = Obvious
 */
#endif // SEARCH_ENGINE_LIN_MORTON_USERINTERFACE_H
