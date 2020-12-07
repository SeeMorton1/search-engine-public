
#ifndef SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#define SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
#include "AvLTree.h"
#include "Index.h"
#include "DocParser.h"
#include "HashTable.h"
class IndexProcessor {
private:
    AvLTree<Index> wordIndex;
    vector<Index> top50;
    HashTable<string,string> authorIndex;
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
            string s = it.returnJsonFileName();
            generateAuthorIndex(authors,s);

            generateIndex(words, it.returnJsonFileName());
        }

    }
    void clearAvL(){
        wordIndex.Clear();
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
            for(int i = 0;i<top50.size();i++){
                if(wordIndex.search(ind)->getData().getCount()>top50.at(i).getCount()){
                    top50.at(i)=wordIndex.search(ind)->getData();
                }
            }
        } else {
            ind.addID(docID);
            ind.addCount();
            wordIndex.insert(ind);
        }
    }
    void generateAuthorIndex(vector<string>& words, string& docID){
        for(auto& it:words){
             string& author = it;

            addAuthorInd(author,docID);
        }
    }
    void addAuthorInd( string &author,  string &docID) {
        authorIndex.insert(author, docID);
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
    HashTable<string,string> getHash(){
        return authorIndex;
    }
    void hashToCsv(ofstream& out){
       for(auto&it:authorIndex.getTable()){
           if(!it.second.empty()){
               out<<it.first<<",";
               for(auto& id:it.second){
                   out<<id<<",";
               }
               out<<endl;
           }
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
    void csvToHash(ifstream& in){
        string s;
        while(getline(in,s)){
            vector<string> words = tokenString(s);
            string authorName = words.at(0);
            for(int i = 1;i<words.size();i++) {
                authorIndex.insert(authorName, words.at(1));
            }
        }
    }
    void setIndex(AvLTree<Index> c){
        wordIndex= c;
    }
    vector<Index> getTop50(){
        levelOrder(wordIndex.getRoot());
        vector<Index> sorted;


        for(int i = 0;i<top50.size();i++){

            for(int j = i;j<top50.size();j++){

                if(top50.at(i).getCount()>top50.at(j).getCount()){
                    swap(top50.at(i),top50.at(j));
                }
            }

        }
        for(int i = 0;i<top50.size()&&i<50;i++){
            sorted.push_back(top50.at(i));
        }


    }

    void levelOrder(AvLTree<Index>::AvLNode* node){
        int h = node->getHeight();
        for(int i = 1;i<=h;i++){
            printLevel(node,i);
        }
    }
    void printLevel(AvLTree<Index>::AvLNode* node,int level){
        if(node== nullptr){
            return;
        }
        if(level ==1){
            Index curr = node->getData();
            top50.push_back(curr);


        }else if(level>1){
            printLevel(node->getLeft(),level-1);
            printLevel(node->getRight(),level-1);
        }

    }




    

};


#endif //SEARCH_ENGINE_LIN_MORTON_INDEXPROCESSOR_H
