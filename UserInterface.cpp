//
// Created by Zihao Lin on 11/25/2020.
//

#include "UserInterface.h"

void UserInterface::startUI(vector<JsonObject> files) {
    cout << "Starting Search Engine" << endl;

    while (true) {

        cout << "What would you like to search for? Insert Close to exit the search engine." << endl;
        cin >> query;
        if (query == "Close" || query == "close") {
            break;
        } else {
            cout << "Searching...." << endl;
            //Implementation goes here
            findObjects(createUniqueIds(addQuery(query)), files);
            if (SearchResults.empty()) {
                cout << "No search Result" << endl;
            } else {
                bool run = true;
                while (run)
                {
                cout << "Printing top 15:" << endl;
                printStats();
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                cout << "Type 1-15 to print the first 300 words of the article" << endl;
                cout << "Type: " << endl << "A) Total number of individual articles indexed" << endl
                     << "B) Average number of words indexed per article" << endl << "C) Total number of unique words "
                     << endl << "D) Total number of unique Authors" << endl << "E) Top 50 most frequent words" << endl
                     << "Type anything else to quit" << endl;
                string input;
                cin >> input;
                if (input == "1" || input == "2" || input == "3" || input == "4" || input == "5" || input == "6" ||
                    input == "7" || input == "8" || input == "9" || input == "10" || input == "11" || input == "12" ||
                    input == "13" || input == "14" || input == "15") {
                    int option = stoi(input);
                    option = option - 1;
                    printArticle(option);
                }
                else if (input == "A"){
                    cout << "Total Number of Articles Indexed: " << returnArticlesIndexed() << endl;
                }
                else if (input == "B"){
                    cout << "Average number of Words per Article: " << averageNumberOfWordsPerArticle() << endl;
                }
                else if (input == "C"){
                    cout << "Total Number of Unique Words: " << returnUniqueWordsNumber() << endl;
                }
                else if (input == "D"){
                    cout << "Total Number of Unique Authors: " << returnUniqueAuthorsNumber() << endl;
                }
                else if (input == "E"){
                    cout << "Top 50 most frequent Words: " << endl;
                }
                else{
                    cout << "Unknown input. Did you wish to exit?" << endl;
                    string input;
                    cin >> input;
                    transform(input.begin(),input.end(),input.begin(),::tolower);
                    if (input == "yes"){
                        run = false;
                    }
                    else if (input == "no"){
                        run = true;
                    }
                    else{
                        cout << "Unknown input" << endl;
                    }
                }
                }
            }


        }
    }
}

list<string> UserInterface::addQuery(string query) {
    Query newQuery;
    newQuery.setIn(query);
    //Needs to have a return from the search engine file
}

vector<string> UserInterface::createUniqueIds(list<string> list) {
    set<string> temp;
    for (const auto &it:list) {
        temp.insert(it);
    }
    vector<string> uniqueIds;
    for (const auto &it:temp) {
        uniqueIds.push_back(it);
    }
    return uniqueIds;
}

void UserInterface::printTop50() {
    for (int i=0; i<50; i++){
        cout << i << ") " << top50Words.at(i).returnWord() << " with " << top50Words.at(i).returnCount() << " counts.";
    }
}


void UserInterface::findObjects(vector<string> jsonIDS, vector<JsonObject> allFiles) {
    for (int i = 0; i < jsonIDS.size(); i++) {
        for (int j = 0; j < allFiles.size(); j++) {
            if (allFiles.at(j).returnJsonFileName() == jsonIDS.at(i)) {
                topRankedArticles.push_back(allFiles.at(j));
            }
        }
    }
}

int UserInterface::returnArticlesIndexed() {
    return SearchResults.size();
}

int UserInterface::averageNumberOfWordsPerArticle() {
    int count = 0;
    for (int i = 0; i < SearchResults.size(); i++) {
        count += SearchResults.at(i).returnText().size();
    }
    count = count / SearchResults.size();
    return count;
}

int UserInterface::returnUniqueAuthorsNumber() {
    set<string> UniqueAuthors;
    for (int i = 0; i < SearchResults.size(); i++) {
        for (int j = 0; j < SearchResults.at(i).returnAuthor().size(); j++) {
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

void UserInterface::printArticle(int x) {
    for (int i = 0; i < 300; i++) {
        cout << topRankedArticles.at(x).returnText().at(i) << " ";
    }
}

void UserInterface::printStats() {
    for (int i = 0; i < 15; i++) {
        cout << "Title: " << SearchResults.at(i).returnTitle() << endl;
        cout << "Author(s): ";
        for (int j = 0; j < SearchResults.at(i).returnAuthor().size(); j++) {
            if (j != SearchResults.at(i).returnAuthor().size() - 1) {
                cout << SearchResults.at(i).returnAuthor().at(j) << ", ";
            } else {
                cout << SearchResults.at(i).returnAuthor().at(j);
                cout << "No publisher";
            }
        }
        cout << endl;
        if (SearchResults.at(i).returnPublisher() != "") {
            cout << "Publisher: " << SearchResults.at(i).returnPublisher() << endl;
        } else {
            cout << "Unknown Publisher" << endl;
        }
        cout << "Publish Date: " << SearchResults.at(i).returnTime() << endl;
        cout << endl;
    }
}