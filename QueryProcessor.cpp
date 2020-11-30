//
// Created by Conner Morton on 11/26/2020.
//
//https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/



#include "QueryProcessor.h"

vector<string> tokenString(const string &str) {
    vector<string> words;
    stringstream ss(str);
    string buff;
    while (getline(ss, buff, ' ')) {
        transform(buff.begin(), buff.end(), buff.begin(), ::tolower);
        words.push_back(buff);
    }
    return words;
}

void  QueryProcessor::genQuery() {

    string i = search;
    vector<string> words = tokenString(i);

    for(int j = 0;j<words.size();j++){
        if(words.at(j)=="and"){
            query.setAndQ(words.at(j+1));
            j++;
        }
        else if(words.at(j)=="or"){
            query.setOr(words.at(j+1));
            j++;
        }
        else if(words.at(j)=="not"){
            query.setNot(words.at(j+1));
            j++;
        }
        else if (words.at(j)=="author"){
            query.setAuthor(words.at(j+1));
            j++;
        }else{
            query.setIn(words.at(j));
        }
    }

}

void QueryProcessor::setSearch(const string &in) {
    search = in;
}

bool isFound(const string& q,vector<string>& w){
    return find(w.begin(),w.end(),q)!=w.end();
}

list<string> &QueryProcessor::findId(DocParser& doc) {
    list<string> foundID;
    vector<JsonObject> jsons =doc.getJsons();
    if(query.hasNot()){
        if(query.hasAnd()){
            for(auto& it:jsons){
                vector<string> words = it.returnText();
                if(isFound(query.getIn(),words)&&isFound(query.getAnd(),words)&&!(isFound(query.getNot(),words))){
                    foundID.push_back(it.returnJsonFileName());
                }
            }
        }else if(query.hasOr()){
            for(auto& it:jsons){
                vector<string> words = it.returnText();
                if(isFound(query.getIn(),words)||(isFound(query.getOr(),words)&&!isFound(query.getNot(),words))){
                    foundID.push_back(it.returnJsonFileName());
                }
            }
        }else{
            for(auto& it:jsons){
                vector<string> words = it.returnText();
                if(isFound(query.getIn(),words)&&!isFound(query.getNot(),words)){
                    foundID.push_back(it.returnJsonFileName());
                }
            }
        }
    }else{
        if(query.hasOr()){
            for(auto& it:jsons){
                vector<string> words=it.returnText();
                if(isFound(query.getIn(),words)||isFound(query.getOr(),words)){

                }
            }
        }else if(query.hasAnd()){
            for(auto& it:jsons){
                vector<string> words = it.returnText();
                if(isFound(query.getIn(),words)||isFound(query.getOr(),words)){

                }
            }
        }else{
            for(auto& it:jsons){
                vector<string> words = it.returnText();
                if(isFound(query.getIn(),words)){

                }
            }
        }
    }
}



