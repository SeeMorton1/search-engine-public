//
// Created by Conner Morton on 11/30/2020.
//

#include "SearchEngine.h"

void SearchEngine::popIndex(const DocParser &doc) {

}
bool vectorContains(const vector<string>& words, const string& s){
    for(auto& it:words){
        if(it==s){
            return true;
        }
    }
    return false;
}

list<string> SearchEngine::findDocs(Query &q) {
    list<string> f;
    if(q.hasAuthor()){
        cout<<"process author first, then words";
    }else{
        string initial = q.getIn();
        Index n;
        n.setWord(initial);
        Index found = wordIndex.search(n)->getData();
        list<string> toSearch = found.getIDs();
        if(q.hasAnd()&&q.hasNot()){
            for(auto& it:toSearch){
                JsonObject file = findObjects(it,jsons); //http://www.cplusplus.com/reference/algorithm/find_if/
                bool isAndFound = vectorContains(file.returnText(),q.getAnd());
               // bool isAndFound(find_if(file.returnText().begin(),file.returnText().end(),q.getAnd())!=file.returnText().end());
               bool isNotFound = vectorContains(file.returnText(),q.getNot());
                //bool isNotFound(find_if(file.returnText().begin(),file.returnText().end(),q.getNot())!=file.returnText().end());
                if(isAndFound&&!isNotFound){
                    f.push_back(it);
                }
            }
            cout<<"process and and not";
        }
        else if(q.hasAnd()){
            for(auto& it:toSearch){
                JsonObject file = findObjects(it,jsons);
                bool isAndFound = vectorContains(file.returnText(),q.getAnd());
                //bool isAndFound(find_if(file.returnText().begin(),file.returnText().end(),q.getAnd())!=file.returnText().end());
                if(isAndFound){
                    f.push_back(it);
                }
            }

        }else if(q.hasOr()&&q.hasNot()){
            Index x;
            x.setWord(q.getOr());
            list<string> orID= wordIndex.search(x)->getData().getIDs();
            for(auto& it: orID){
                JsonObject file =findObjects(it,jsons);
                bool isNotFound = vectorContains(file.returnText(),q.getNot());
//                bool isNotFound  = (find_if(file.returnText().begin(),file.returnText().end(),q.getNot())!=file.returnText().end());
                if(!isNotFound){
                    f.push_back(it);
                }
            }
            for(auto& it:toSearch){
                JsonObject file =findObjects(it,jsons);
                bool isNotFound = vectorContains(file.returnText(),q.getNot());
                if(!isNotFound){
                    f.push_back(it);
                }
            }
            cout<<"process or and not";
        }else if(q.hasOr()) {
            Index x;
            x.setWord(q.getOr());
            list<string> orID = wordIndex.search(x)->getData().getIDs();
            for(auto&  it: orID){
                f.push_back(it);
            }
            for(auto& it:toSearch){
                f.push_back(it);
            }

        }else{
            for(auto& it:toSearch){
                f.push_back(it);
            }
            cout<<"found";
        }
    }
    return f;
}

JsonObject &SearchEngine::findObjects(const string& id, vector<JsonObject>& files) {
    for(auto & file : files){
        if(file.returnJsonFileName()==id){
            return file;
        }
    }
}

void SearchEngine::setFiles(vector<JsonObject> &files) {
    jsons = files;
}

