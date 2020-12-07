//
// Created by Conner Morton on 11/30/2020.
//

#include "SearchEngine.h"


bool vectorContains(const vector<string>& words, const string s){

    return find(words.begin(),words.end(),s)!=words.end();
}

list<string> SearchEngine::findDocs(Query &q, AvLTree<Index>& wordIndex, HashTable<string, string> table, const char* fi, ifstream& stop, ifstream& csv) {
    list<string> f;

    if(q.hasAuthor()){
        pair<string, vector<string>> p;

        string s = q.getAuthor();

        if(table.isFound(s)){
            p = table.getPair(s);
        }

        if (q.hasIn() && q.hasAnd() && q.hasNot()) {
            Index in;
            in.setWord(q.getIn());
            Index andIndex;
            andIndex.setWord(q.getAnd());
            Index notIndex;
            notIndex.setWord(q.getNot());
            if (wordIndex.isFound(in)) {
                in = wordIndex.search(in)->getData();
            } else {
                cout << "not found" << endl;
            }
            if (wordIndex.isFound(andIndex)) {
                andIndex = wordIndex.search(andIndex)->getData();
            } else {
                cout << "not found" << endl;
            }
            if (wordIndex.isFound(notIndex)) {
                notIndex = wordIndex.search(notIndex)->getData();
            }
            for (auto &it:p.second) {
                for (auto &id:in.getIDs()) {
                    if (it == id) {
                        for (auto &ip:andIndex.getIDs()) {
                            if (it == ip) {
                                for (auto &ic:notIndex.getIDs()) {
                                    if (ic != it) {
                                        f.push_back(it);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else if (q.hasIn() && q.hasOr() && q.hasNot()) {
            Index in;
            in.setWord(q.getIn());
            Index orIndex;
            orIndex.setWord(q.getOr());
            Index notIndex;
            notIndex.setWord(q.getNot());
            if (wordIndex.isFound(in)) {
                in = wordIndex.search(in)->getData();
            }
            if (wordIndex.isFound(orIndex)) {
                orIndex = wordIndex.search(orIndex)->getData();
            }
            if (wordIndex.isFound(notIndex)) {
                notIndex = wordIndex.search(notIndex)->getData();
            }

            for (auto &it:p.second) {
                for (auto &id:in.getIDs()) {
                    if (it == id) {
                        for (auto &ic:notIndex.getIDs()) {
                            if (it != ic) {
                                f.push_back(it);
                            }
                        }
                    }
                }
                for (auto &id:orIndex.getIDs()) {
                    if (it == id) {
                        for (auto &ic:notIndex.getIDs()) {
                            if (it != ic) {
                                f.push_back(it);
                            }
                        }
                    }
                }
            }
        } else if (q.hasIn() && q.hasAnd()) {
            Index in;
            in.setWord(q.getIn());
            Index andIndex;
            andIndex.setWord(q.getAnd());
            if (wordIndex.isFound(in)) {
                in = wordIndex.search(in)->getData();
            } else {
                cout << "not found" << endl;
            }
            if (wordIndex.isFound(andIndex)) {
                andIndex = wordIndex.search(andIndex)->getData();
            } else {
                cout << "not found" << endl;
            }
            for (auto &it:p.second) {
                for (auto &id:in.getIDs()) {
                    if (it == id) {
                        for (auto &ic:andIndex.getIDs()) {
                            if (it == ic) {
                                f.push_back(it);
                            }
                        }
                    }
                }
            }
        } else if (q.hasIn() && q.hasOr()) {
            Index in;
            in.setWord(q.getIn());
            Index orIndex;
            orIndex.setWord(q.getOr());
            if (wordIndex.isFound(in)) {
                in = wordIndex.search(in)->getData();
            }
            if (wordIndex.isFound(orIndex)) {
                orIndex = wordIndex.search(orIndex)->getData();
            }
            for (auto &it:p.second) {
                for (auto &id:in.getIDs()) {
                    if (it == id) {
                        f.push_back(it);
                    }
                }
                for (auto &id:orIndex.getIDs()) {
                    if (id == it) {
                        f.push_back(it);
                    }
                }
            }

        } else if (q.hasIn()) {
            Index in;
            in.setWord(q.getIn());
            if (wordIndex.isFound(in)) {
                in = wordIndex.search(in)->getData();
            }
            for (auto &it:p.second) {
                for (auto &id:in.getIDs()) {
                    if (it == id) {
                        f.push_back(it);
                    }
                }
            }
        } else {
            for (auto &it:p.second) {
                f.push_back(it);
            }
        }




    }else{
        string initial = q.getIn();
        Index n;
        n.setWord(initial);
        Index found;
        if(wordIndex.isFound(n)){
            found = wordIndex.search(n)->getData();
        }else{
            cout<<"Not found"<<endl;
        }

        list<string> toSearch = found.getIDs();
        set<string> setToSearch;
        for(auto& it:toSearch){
            setToSearch.insert(it);
        }
        bool proAnd = q.hasAnd();
        bool proNot = q.hasNot();

        if (q.hasAnd() && q.hasNot()) {
            for (auto &it:setToSearch) {
                JsonObject file = findFile(it,fi,stop,csv);//http://www.cplusplus.com/reference/algorithm/find_if/
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
            Index andInitial;
            andInitial.setWord(q.getAnd());
            Index andIn = wordIndex.search(andInitial)->getData();
            set<string> andSet;
            for(auto& it:andIn.getIDs()){
                andSet.insert(it);
            }
            for (auto &it:setToSearch) {
                for(auto& itAnd:andSet){
                    if(it==itAnd){
                        f.push_back(it);
                    }
                }
//            JsonObject file = findFile(it,fi,stop,csv);
//
//            bool isAndFound = vectorContains(file.returnText(), q.getAnd());
//            //bool isAndFound(find_if(file.returnText().begin(),file.returnText().end(),q.getAnd())!=file.returnText().end());
//
//            if (isAndFound) {
//                f.push_back(it);
//            }
            }
            for(auto& it:andSet){
                for(auto& id:setToSearch){
                    if(it==id){
                        f.push_back(it);
                    }
                }
            }//and branch tree

        } else if (q.hasOr() && q.hasNot()) {
            Index x;
            x.setWord(q.getOr());
            list<string> orID = wordIndex.search(x)->getData().getIDs();
            set<string> setOrID;
            Index notInd ;
            notInd.setWord(q.getNot());
            if(wordIndex.isFound(notInd)){
                notInd = wordIndex.search(notInd)->getData();
            }
            bool notFoundOr = false;
            bool notFound = false;
            for(const auto& it:orID){
                setOrID.insert(it);
            }
            for (auto &it: setOrID) {
                JsonObject file = findFile(it,fi,stop,csv);
                bool isNotFound = vectorContains(file.returnText(), q.getNot());

                for(auto& id:notInd.getIDs()){
                    if(id==it){
                        notFoundOr = true;
                    }
                }
//                bool isNotFound  = (find_if(file.returnText().begin(),file.returnText().end(),q.getNot())!=file.returnText().end());
                if (!notFoundOr) {
                    f.push_back(it);
                }
            }
            for (auto &it:setToSearch) {
                for(auto&id:notInd.getIDs()){
                    if(id==it)
                        notFound=true;
                }

                if (!notFound) {
                    f.push_back(it);
                }
            }
            cout << "process or and not";
        } else if (q.hasOr()) {
            Index x;
            x.setWord(q.getOr());
            list<string> orID = wordIndex.search(x)->getData().getIDs();
            set<string> setOrID;
            for(const auto& it:orID){
                setOrID.insert(it);
            }
            for (auto &it: setOrID) {
                f.push_back(it);
            }
            for (auto &it:setToSearch) {
                f.push_back(it);
            }

        } else {

            for (auto &it:toSearch) {
                f.push_back(it);
            }

            cout << "found";
        }
    }




    return f;
}

JsonObject SearchEngine::findObjects(const string& id) {
    for(auto& it:jsons){
        if(it.returnJsonFileName()==id){
            return it;
        }
    }
}
JsonObject SearchEngine::findFile(string id, const char *file,ifstream& stop, ifstream& csv) {
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
        if(wordIndex.isFound(inIndex)){
            inIndex = wordIndex.search(inIndex)->getData();
        }

    }
    if(!a.empty()){
        aIndex.setWord(a);
        if(wordIndex.isFound(aIndex)){
            aIndex = wordIndex.search(aIndex)->getData();
        }

    }
    if(!o.empty()){
        oIndex.setWord(o);
        if(wordIndex.isFound(oIndex)){
            oIndex = wordIndex.search(oIndex)->getData();
        }

    }
    if(!n.empty()){
        nIndex.setWord(n);
        nIndex= wordIndex.search(nIndex)->getData();
    }
    set<string> uniqueIn;
    for(auto& it:inIndex.getIDs()){
        uniqueIn.insert(it);
    }

    for(auto it:uniqueIn){

        JsonObject toPush = findFile(it,file,stop,csv);

        jsons.push_back(toPush);
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




