
#ifndef SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#define SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#include "AvLTree.h"
#include "Index.h"
#include "DocParser.h"
#include "HashTable.h"
class IndexProcessor {
private:
    AvLTree<Index> wordIndex;
    HashTable<string,list<string>> authorIndex;
public:
    IndexProcessor() = default;

    ~IndexProcessor() = default;

    IndexProcessor(const IndexProcessor &copy) {
        wordIndex = copy.wordIndex;

    }
    vector<string> tokenString(const string &str) {
        vector<string> words;
        stringstream ss(str);
        string buff;
        while (getline(ss, buff, ',')) {
            transform(buff.begin(), buff.end(), buff.begin(), ::tolower);
            words.push_back(buff);
        }
        return words;
    }

    void createIndex(DocParser &doc) {

        vector<JsonObject> jsons = doc.getJsons();
        for (auto &it:jsons) {
            vector<string> words = it.returnText();
            vector<string> authors = it.returnAuthor();

            generateAuthorIndex(authors,it.returnJsonFileName());

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
    void generateAuthorIndex(const vector<string>& words,const string& docID){
        for(auto& it:words){
            const string& author = it;
            addAuthorInd(author,docID);
        }
    }
    void addAuthorInd(const string &author, const string &docID) {

        list<string> f;
        f.push_back(docID);
        authorIndex.insert(author, f);


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
    void hashToCsv(ofstream& out){
        vector<vector<pair<string,list<string>>>> table = authorIndex.getTable();
        for(auto& it:table){

        }
    }
    void toCSV(ofstream& out){
        AvLTree<Index>::AvLNode* root = wordIndex.getRoot();
        write(root,out);
    }
    void write( AvLTree<Index>::AvLNode* node,ofstream& out){
        levelOrder(node,out);
    }
    void levelOrder(AvLTree<Index>::AvLNode* node,ofstream& out){
        int h = node->getHeight();
        for(int i = 1;i<=h;i++){
            printLevel(node,i,out);
        }
    }
    void printLevel(AvLTree<Index>::AvLNode* node,int level, ofstream& out){
        if(node== nullptr){
            return;
        }
        if(level ==1){
            Index curr = node->getData();
            out<<curr.getWord()<<",";
            for(auto& it: curr.getIDs()){
                out<<it<<",";
            }

            out<<'\n';
        }else if(level>1){
            printLevel(node->getLeft(),level-1,out);
            printLevel(node->getRight(),level-1,out);
        }

    }
    AvLTree<Index>& csvToTree(ifstream& in){
        string s;
        while(getline(in,s)){
            vector<string> words = tokenString(s);
            Index c;
            c.setWord(words.at(0));
            for(int i = 1;i<words.size();i++){
                c.addID(words.at(i));
            }
            wordIndex.insert(c);
        }
        return wordIndex;

    }
    void setIndex(AvLTree<Index> c){
        wordIndex= c;
    }

    

};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
