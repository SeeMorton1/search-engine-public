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
            if(wordIndex.isFound(c)){
                AvLNode<Index>* f = wordIndex.search(wordIndex.getRoot(),c);
                f->getData().addCount();
                f->getData().addID(it.returnJsonFileName());


            }else{
                c.addID(it.returnJsonFileName());
                wordIndex.insert(c);
            }
        }
    }
}
