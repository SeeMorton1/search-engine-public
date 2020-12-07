//
// Created by Conner Morton on 11/30/2020.
//

#include "SearchEngine.h"


bool vectorContains(const vector<string>& words, const string s){

    return find(words.begin(),words.end(),s)!=words.end();
}

list<string> SearchEngine::findDocs(Query &q,AvLTree<Index>& wordIndex) {
    list<string> f;


    string initial = q.getIn();
    Index n;
    n.setWord(initial);
    Index found = wordIndex.search(n)->getData();
    list<string> toSearch = found.getIDs();
    bool proAnd = q.hasAnd();
    bool proNot = q.hasNot();

    if (q.hasAnd() && q.hasNot()) {
        for (auto &it:toSearch) {
            JsonObject file = findObjects(it); //http://www.cplusplus.com/reference/algorithm/find_if/
            bool isAndFound = vectorContains(file.returnText(), q.getAnd());
            // bool isAndFound(find_if(file.returnText().begin(),file.returnText().end(),q.getAnd())!=file.returnText().end());
            bool isNotFound = vectorContains(file.returnText(), q.getNot());
            //bool isNotFound(find_if(file.returnText().begin(),file.returnText().end(),q.getNot())!=file.returnText().end());
            if (isAndFound && !isNotFound) {
                f.push_back(it);
            }
        }
        cout << "process and and not";
    } else if (q.hasAnd()) {

        for (auto &it:toSearch) {
            JsonObject file = findObjects(it);
            bool isAndFound = vectorContains(file.returnText(), q.getAnd());
            //bool isAndFound(find_if(file.returnText().begin(),file.returnText().end(),q.getAnd())!=file.returnText().end());

            if (isAndFound) {
                f.push_back(it);
            }
        }//and branch tree

    } else if (q.hasOr() && q.hasNot()) {
        Index x;
        x.setWord(q.getOr());
        list<string> orID = wordIndex.search(x)->getData().getIDs();

        for (auto &it: orID) {
            JsonObject file = findObjects(it);
            bool isNotFound = vectorContains(file.returnText(), q.getNot());
//                bool isNotFound  = (find_if(file.returnText().begin(),file.returnText().end(),q.getNot())!=file.returnText().end());
            if (!isNotFound) {
                f.push_back(it);
            }
        }
        for (auto &it:toSearch) {
            JsonObject file = findObjects(it);
            bool isNotFound = vectorContains(file.returnText(), q.getNot());
            if (!isNotFound) {
                f.push_back(it);
            }
        }
        cout << "process or and not";
    } else if (q.hasOr()) {
        Index x;
        x.setWord(q.getOr());
        list<string> orID = wordIndex.search(x)->getData().getIDs();
        for (auto &it: orID) {
            f.push_back(it);
        }
        for (auto &it:toSearch) {
            f.push_back(it);
        }

    } else {
        for (auto &it:toSearch) {
            f.push_back(it);
        }
        cout << "found";
    }



    return f;
}

JsonObject &SearchEngine::findObjects(const string& id) {
    for(auto& it:jsons){
        if(it.returnJsonFileName()==id){
            return it;
        }
    }
}
JsonObject& SearchEngine::findFile(string id, const char *file,ifstream& stop, ifstream& csv) {
    DocParser newParser;
    JsonObject newObject = newParser.parseAFile(id,file,stop,csv);

    return newObject;
}
void SearchEngine::populateJsons(Query q,AvLTree<Index> wordIndex, const char* file,ifstream& stop,ifstream& csv){
    string in = q.getIn();
    string a = q.getAnd();
    string o = q.getOr();
    string n = q.getNot();
    Index inIndex;
    Index aIndex;
    Index oIndex;
    Index nIndex;
    if(!in.empty()){
        inIndex.setWord(in);
        inIndex = wordIndex.search(inIndex)->getData();
    }
    if(!a.empty()){
        aIndex.setWord(a);
        if(wordIndex.isFound(aIndex)){
            aIndex = wordIndex.search(aIndex)->getData();
        }

    }
    if(!o.empty()){
        oIndex.setWord(o);
        oIndex = wordIndex.search(oIndex)->getData();
    }
    if(!n.empty()){
        nIndex.setWord(n);
        nIndex= wordIndex.search(nIndex)->getData();
    }

    for(auto& it:inIndex.getIDs()){

        jsons.push_back(findFile(it,file,stop,csv));
    }
    for(auto& it:aIndex.getIDs()){
        jsons.push_back(findFile(it,file,stop,csv));
    }
    for(auto& it:oIndex.getIDs()){
        jsons.push_back(findFile(it,file,stop,csv));
    }
    for(auto& it:nIndex.getIDs()){
        jsons.push_back(findFile(it,file,stop,csv));
    }

}

void SearchEngine::setFiles(vector<JsonObject> files) {
    jsons = files;
}




