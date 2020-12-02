
#ifndef SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#define SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#include "AvLTree.h"
#include "Index.h"
#include "DocParser.h"

class IndexProcessor {
private:
    AvLTree<Index> wordIndex;
public:
    IndexProcessor() = default;

    ~IndexProcessor() = default;

    IndexProcessor(const IndexProcessor &copy) {
        wordIndex = copy.wordIndex;

    }

    void createIndex(DocParser &doc) {
        vector<JsonObject> jsons = doc.getJsons();
        for (auto &it:jsons) {
            vector<string> words = it.returnText();

            generateIndex(words, it.returnJsonFileName());
        }
    }

    list<string> findWord(const string &w) {
        Index sea;
        sea.setWord(w);
        list<string> i;
        if(wordIndex.isFound(sea)){
            i = wordIndex.search(sea)->getData().getIDs();
        }

        return i;
    }

    //static list<string> findIDS(const string& look, DocParser &doc);

    void addInd(Index &ind, const string &docID) {
        bool f = wordIndex.isFound(ind);
        if (f) {

            wordIndex.search(ind)->getData().addID(docID);
        } else {
            ind.addID(docID);
            ind.addCount();
            wordIndex.insert(ind);
        }
    }

    void generateIndex(const vector<string> &words, const string &docID) {
        for (auto &it:words) {
            Index p;
            p.setWord(it);
            addInd(p, docID);
        }
    }
    AvLTree<Index>& getIndex(){
        return wordIndex;
    }

};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
