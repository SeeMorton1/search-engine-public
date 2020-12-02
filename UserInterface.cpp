//
// Created by Zihao Lin on 11/25/2020.
//

#include "UserInterface.h"
void UserInterface::startUI(vector<JsonObject> files)
{
    cout << "Starting Search Engine" << endl;

    while (true)
    {

        cout << "What would you like to search for? Insert Close to exit the search engine." << endl;
        cin >> query;
        if (query == "Close" || query == "close"){
            break;
        }
        else{
            cout << "Searching...." << endl;
            findObjects(createUniqueIds(addQuery(query)),files);
        }
    }
}

list<string> UserInterface::addQuery(string query)
{
    Query newQuery;
    newQuery.setIn(query);
    //Needs to have a return from the search engine file
}

vector<string> UserInterface::createUniqueIds(list<string> list) {
    set<string> temp;
    for (const auto &it:list){
        temp.insert(it);
    }
    vector<string> uniqueIds;
    for (const auto &it:temp){
        uniqueIds.push_back(it);
    }
    return uniqueIds;
}


void UserInterface::findObjects(vector<string> jsonIDS, vector<JsonObject> allFiles) {
    for (int i=0; i<jsonIDS.size();i++){
        for (int j=0; j<allFiles.size();j++){
            if (allFiles.at(j).returnJsonFileName() == jsonIDS.at(i)){
                SearchResults.push_back(allFiles.at(j));
            }
        }
    }
}

int UserInterface::returnArticlesIndexed() {
    return SearchResults.size();
}

int UserInterface::averageNumberOfWordsPerArticle() {
    int count = 0;
    for (int i=0; i<SearchResults.size();i++){
        count += SearchResults.at(i).returnText().size();
    }
    count = count/SearchResults.size();
    return count;
}

int UserInterface::returnUniqueAuthorsNumber() {
    set<string> UniqueAuthors;
    for (int i=0; i<SearchResults.size();i++){
        for (int j=0;j<SearchResults.at(i).returnAuthor().size();j++){
            UniqueAuthors.insert(SearchResults.at(i).returnAuthor().at(j));
        }
    }
    return UniqueAuthors.size();
}

void UserInterface::setCount(long Nodes) {
    sizeOfNode = Nodes;
}

int UserInterface::returnUniqueWordsNumber() {
    return sizeOfNode;
}

void UserInterface::printArticle(JsonObject article) {
    for (int i=0; i< 300; i++){
        cout << article.returnText().at(i) << " ";
    }
}
void UserInterface::printStats(){
    for (int i=0; i<15 ;i++){
        cout << "Title: " << SearchResults.at(i).returnTitle() << endl;
        cout << "Author(s): ";
        for(int j=0; j<SearchResults.at(i).returnAuthor().size();j++){
            if (j != SearchResults.at(i).returnAuthor().size()-1) {
                cout << SearchResults.at(i).returnAuthor().at(j) << ", ";
            }
            else{
                cout << SearchResults.at(i).returnAuthor().at(j);
            }
        }
        cout << endl;
        cout << "Publisher: " << SearchResults.at(i).returnPublisher() << endl;
        cout << "Publish Date: " << SearchResults.at(i).returnTime() << endl;
        cout << endl;
    }
}