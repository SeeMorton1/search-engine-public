//
// Created by Zihao Lin on 11/25/2020.
//

#include "UserInterface.h"
/*
 * To DO List:
 * Write Index (Option 1)
 * Open CSV File (Option 3)
 * Clear Index (Option 4)
 * Function returnUniqueWordsNumber() aka Nodes in avl
 * 
 */
void UserInterface::startUI(const char *file, ifstream &stopWords, ifstream &csvFile) {
    cout << "Starting Search Engine" << endl;
    bool RunUI = true;

    while (RunUI) {
        string UserInput;
        cout << "Choose an Option" << endl << "~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "1.Write Index\n2.Create Index\n3.Open CSV File\n4.Clear Index\n5.Search\n6.Display Stats\n7.Exit"
             << endl;
        cin >> UserInput;
        int Option;
        if(!UserInput.empty()){
            Option = stoi(UserInput);
        }

        if (Option == 1 || Option == 2 || Option == 3 || Option == 4 || Option == 5 || Option == 6 || Option == 7) {
            if (Option == 1) {
                string fileName;
                cout<<"Please enter file to save word index to in the form 'fileToSave.csv'"<<endl;
                cin>>fileName;
                string authorFileName;
                //cout<<"Please enter file to save author index to in the form 'fileToSave.csv'"<<endl;
                //cin>>authorFileName;
                ofstream out(fileName);
                //ofstream outAuthor(authorFileName);
                IndexProcessor p;
                p.setIndex(wordIndex);
                //p.setAuthorIndex(authorIndex);
                //p.toAuthorCsv(outAuthor);
                p.toCSV(out);
                //Write index - writes the current Index(AVL TRee and HAsh table) in the program to the CSV
            } else if (Option == 2) {

                DocParser newParse;
                newParse.parseFiles(file, stopWords, csvFile);

                IndexProcessor p;

                p.createIndex(newParse);

                wordIndex=p.getIndex();
                VectorOfJsons = newParse.getJsons();
            } else if (Option == 3) {
                string filePath;
                cout<<"Please input the absolute path to the csv file"<<endl;
                cin>>filePath;
                ifstream fileToRead(filePath);
                IndexProcessor p;
                wordIndex = p.csvToTree(fileToRead);
                //Open file - Opens the CSV for quick access to the AVL tree
            } else if (Option == 4) {
                //clearIndex(); //Don't have a function written out for this yet
            } else if (Option == 5) {
                cout << "What would you like to search for?" << endl;
                Query newQuery;
                cin >> query;
                QueryProcessor queryProcessor;
                queryProcessor.setSearch(query);

                newQuery.setIn(queryProcessor.getQuery().getIn());newQuery.setAndQ(queryProcessor.getQuery().getAnd());newQuery.setOr(queryProcessor.getQuery().getOr());newQuery.setNot(queryProcessor.getQuery().getNot());newQuery.setAuthor(queryProcessor.getQuery().getAuthor());

                SearchEngine newSearch;
                //Clears the Result Vectors before doing new Search
                SearchResults.clear();
                topRankedArticles.clear();
                //This line pretty much takes List<string> and converts it to vector of string of unique ids and finds their object
                //THen I put it into SearchResults
                findObjects(createUniqueIds(newSearch.findDocs(newQuery,wordIndex)), VectorOfJsons);
                if (SearchResults.size() > 1) {
                    bool run = true;
                    while (run) {
                        cout << "Printing top 15 Articles:" << endl;
                        printStats();
                        cout << "Choose an Option 1-" << topRankedArticles.size()
                             << " to see first 300 words or type 0 to EXIT" << endl;
                        int option;
                        cin >> option;
                        if (option <= topRankedArticles.size() && option > 0) {
                            option = option - 1;
                            printArticle(option);
                        } else if (option == 0) {
                            run = false;
                        } else {
                            cout << "Invalid Option. Please Try Again" << endl;
                        }
                    }
                } else {
                    cout << "No Search Results" << endl;
                }
            } else if (Option == 6) {
                cout << "Choose an Option" << endl << "~~~~~~~~~~~~~~~~~~~" << endl;
                cout
                        << "1.Total number of individual articles indexed\n2.Average number of words indexed per article\n3.Total number of unique words indexed\n4.Total number of unique Authors\n5.Top 50 most frequent words\nAnything Else To EXIT"
                        << endl;
                int option;
                cin >> option;
                if (option >= 1 && option <= 5) {
                    if (option == 1) {
                        cout << "Total Number of Articles Indexed: " << returnArticlesIndexed() << endl;
                    } else if (option == 2) {
                        cout << "Average number of Words per Article: " << averageNumberOfWordsPerArticle() << endl;
                    }
                    else if (option == 3){
                        cout << "Number of Unique Words: " << returnUniqueWordsNumber() << endl;
                    }
                    else if (option == 4){
                        cout << "Number of Unique Authors: " <<returnUniqueAuthorsNumber() << endl;
                    }
                    else if (option == 5){
                        cout << "Printing Top 50 Words:" << endl;
                        printTop50();
                    }
                } else {
                    cout << "Returning To Search Engine..." << endl << endl;
                }
            } else if (Option == 7) {
                cout << "Exiting Search Engine" << endl;
                RunUI = false;
            }
        } else {
            cout << "Invalid Option." << endl;
        }
    }
}



vector<string> UserInterface::createUniqueIds(list<string> list) {
    set<string> temp;
    for (const auto &it:list) {
        temp.insert(it);
    }
    vector<string> uniqueIds;
    for (const auto &it:temp) {
        uniqueIds.push_back(it);
    }
    return uniqueIds;
}

void UserInterface::printTop50() {
    for (int i = 0; i < 50; i++) {
        cout << i << ") " << top50Words.at(i).returnWord() << " with " << top50Words.at(i).returnCount() << " counts.";
    }
}


void UserInterface::findObjects(vector<string> jsonIDS, vector<JsonObject> allFiles) {
    for (int i = 0; i < jsonIDS.size(); i++) {
        for (int j = 0; j < allFiles.size(); j++) {
            if (allFiles.at(j).returnJsonFileName() == jsonIDS.at(i)) {
                numberOfWords += allFiles.at(j).returnText().size();
                numberOfIndex++;
                SearchResults.push_back(allFiles.at(j));
            }
        }
    }
    addAuthors();
}

void UserInterface::addAuthors() {
    for (int i=0; i<SearchResults.size();i++) {
        for (int j=0; j<SearchResults.at(i).returnAuthor().size();j++){
            Authors.push_back(SearchResults.at(i).returnAuthor().at(j));
        }
    }
}

long UserInterface::returnArticlesIndexed() {
    return numberOfIndex;
}

long UserInterface::averageNumberOfWordsPerArticle() {
    long AVGWords = numberOfWords / numberOfIndex;
    return AVGWords;
}

int UserInterface::returnUniqueAuthorsNumber() {
    set<string> UniqueAuthors;
    for (int i = 0; i < Authors.size(); i++) {
        UniqueAuthors.insert(Authors.at(i));
    }
    return UniqueAuthors.size();
}

void UserInterface::setCount(long Nodes) {
    sizeOfNode = Nodes;
}

long UserInterface::returnUniqueWordsNumber() {
    return sizeOfNode;
}

void UserInterface::printArticle(int x) {
    for (int i = 0; i < 300; i++) {
        cout << topRankedArticles.at(x).returnText().at(i) << " ";
    }
}

void UserInterface::printStats() {
    for (int i = 0; i < 15; i++) {
        cout << i << ") Title: " << SearchResults.at(i).returnTitle() << endl;
        cout << "Author(s): ";
        for (int j = 0; j < SearchResults.at(i).returnAuthor().size(); j++) {
            if (j != SearchResults.at(i).returnAuthor().size() - 1) {
                cout << SearchResults.at(i).returnAuthor().at(j) << ", ";
            } else {
                cout << SearchResults.at(i).returnAuthor().at(j);
                cout << "No publisher";
            }
        }
        cout << endl;
        if (SearchResults.at(i).returnPublisher() != "") {
            cout << "Publisher: " << SearchResults.at(i).returnPublisher() << endl;
        } else {
            cout << "Unknown Publisher" << endl;
        }
        cout << "Publish Date: " << SearchResults.at(i).returnTime() << endl;
        cout << endl;
    }
}

void UserInterface::processIndex(const char *file, const char *csv, const char *stop) {
    DocParser docParser;
    ifstream stopFile(stop);
    ifstream csvFile(csv);
    docParser.parseFiles(file,stopFile,csvFile);
    IndexProcessor p;
    p.createIndex(docParser);
    wordIndex=p.getIndex();
    //authorIndex=p.getAuthorIndex();
}

void UserInterface::clearIndex() {
    wordIndex.Clear();
}


