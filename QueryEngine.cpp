//
// Created by Zihao Lin on 11/25/2020.
//

#include "QueryEngine.h"

QueryEngine::QueryEngine() = default;

QueryEngine::~QueryEngine() = default;

QueryEngine::QueryEngine(QueryEngine& copy)
{

}

void QueryEngine::queryHandler(string query)
{
    string word = "";
    for (auto x:query){
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (x == ' ') {
                    Porter2Stemmer::stem(word);
                    addWord(word);
                word = "";
        } else if ((x<33 || x>47) && (x>64 || x <58)){
            word = word + x;
        }
    }
}
void QueryEngine::addWord(string word)
{
    query.push_back(word);
}
void QueryEngine::setNumberOfWords()
{
    for (int i=0; i<query.size();i++){
        if (query.at(i) != "AND" && query.at(i) != "OR" && query.at(i) != "NOT" && query.at(i) != "AUTHOR"){
            numberOfWords++;
        }
    }
}
