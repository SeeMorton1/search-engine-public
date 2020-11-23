//
// Created by Conner Morton on 11/21/2020.
//

#include "IndexProcessor.h"

void IndexProcessor::createIndex(DocParser &doc) {
    vector<JsonObject> jsons = doc.getJsons();
    for(auto& it:jsons){
        vector<string> words = it.returnText();

        for(auto& word:words){
            Index c;
            c.setWord(word);
            if (wordIndex.isFound(wordIndex.getRoot(), c)) {
                AvLNode<Index> *f = wordIndex.searchAlgo(wordIndex.getRoot(), c);
                f->getData().addCount();
                f->getData().addID(it.returnJsonFileName());

            } else {
                c.addID(it.returnJsonFileName());
                wordIndex.insert(c);
            }
        }

    }
}

list<string> IndexProcessor::findWord(string w) {
    Index sea;
    sea.setWord(w);
    list<string> i = wordIndex.searchAlgo(wordIndex.getRoot(), sea)->getData().getIDs();

    return i;

}
