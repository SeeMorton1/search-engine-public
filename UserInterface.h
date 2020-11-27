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

using namespace std;

class UserInterface
{
  private:
    vector<JsonObject> topRankedArticles;
    int numberOfIndex;
    int uniqueAuthors;

    string query;
  public:
    void startUI(); //Overall User Interface
    void clearIndex(); //Cleans Index
    void addQuery(string query); //Need to include stem and remove stop words in function
    void printArticle(JsonObject article); //300 Words of article
    int returnQuerySize(); //Returns vector size;

    //Statistical Things
    int returnArticlesIndexed();
    int averageNumberOfWordsPerArticle(JsonObject article);
    int returnUniqueWordsNumber; //Number of Nodes in avl
    int returnUniqueAuthorsNumber;
    








};

/*
 * The user interface of the application should provide the following options:
~allows the user to clear the index completely
~allows the user to parse the corpus and populate index OR open a persistence file.
~allow the user to enter a properly formatted Boolean query (as described above).
The results should display the article’s identifying/important information such as title, authors (at least the first), publication, date published.  The result set shown to the user need not contain any more than the top 15 ranked articles.  If you’d like to show more, you may wish to paginate.
The user should be allowed to choose one of the articles from the result set above and have the first ~300 words of the article printed.
Helpful Hint:  that the query terms should have stop words removed and stemmed before querying the index.
Print basic statistics of the search engine including:
~Total number of individual articles indexed
~Average number of words indexed per article (after removal of stop words)
~Total number of unique words indexed (after stop word removal).  Essentially, the number of nodes in the AVL Tree.
~Total number of unique Authors.
~Top 50 most frequent words (after removal of stop words)
~Any other options you deem appropriate and useful.

 *
 *
 *
 */
#endif // SEARCH_ENGINE_LIN_MORTON_USERINTERFACE_H
