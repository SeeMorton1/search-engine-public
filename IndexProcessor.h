//
// Created by Conner Morton on 11/21/2020.
//

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

    void createIndex(DocParser &doc);

    list<string> findWord(string w);


};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
