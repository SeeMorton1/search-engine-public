//
// Created by Zihao Lin on 11/25/2020.
//  11/27 - Parsing in query and setting up UI
//  11/30 - Added an option to parse from UI
// 12/01 - Started printing Stats
// 12/03 - UI is setup and ready for Morton to implement Index commands
// 12/06 Statistical things work and just finishing up on UI

#include "UserInterface.h"

void UserInterface::startUI(const char *file, ifstream &stopWords, ifstream &csvFile) {
    numberOfIndex = 0;
    numberOfWords = 0;
    cout << "Starting Search Engine" << endl;
    bool RunUI = true;

    while (RunUI) {
        string UserInput;
        cout << "Choose an Option" << endl << "~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "1.Write Index\n2.Create Index\n3.Open CSV File\n4.Clear Index\n5.Search\n6.Search (No Ranking)\n7.Display Stats\n8.Exit"
             << endl;
        cin >> UserInput;


        if (UserInput == "1" || UserInput == "2" || UserInput == "3" || UserInput == "4" || UserInput == "5" ||
            UserInput == "6" || UserInput == "7" || UserInput == "8") {
            if (UserInput == "1") {
                string fileName;
                cout << "Please enter file to save word index to in the form 'fileToSave.csv'" << endl;
                cin >> fileName;
                string authorFileName;
                ofstream out(fileName);
                cout << "Please enter file to save author index to in the form 'fileToSave.csv'" << endl;
                cin >> authorFileName;
                p.toCSV(out);
                out.close();
                ofstream outAuthor(authorFileName);

                p.hashToCsv(outAuthor);

                //p.setAuthorIndex(authorIndex);
                //p.toAuthorCsv(outAuthor);


                //Write index - writes the current Index(AVL TRee and HAsh table) in the program to the CSV
            } else if (UserInput == "2") {
                ofstream pers("persistance.txt");
                DocParser newParse;
                newParse.parseFiles(file, stopWords, csvFile);
                p.createIndex(newParse);
                VectorOfJsons = newParse.getJsons();
                numberOfIndex += newParse.getJsons().size();
                pers << numberOfIndex << endl;
                for (int i = 0; i < newParse.getJsons().size(); i++) {
                    numberOfWords += newParse.getJsons().at(i).returnText().size();
                }
                pers << averageNumberOfWordsPerArticle() << endl;
                setCount(p.getIndex().returnSize());
                pers << returnUniqueWordsNumber() << endl;
                addAuthors(newParse);

                pers << p.getHash().getSize() << endl;


                pers.close();

            } else if (UserInput == "3") {
                ifstream stats("persistance.txt");
                string buff;
                getline(stats, buff);
                numberOfIndex = stoi(buff);
                getline(stats, buff);
                numberOfWords = stoi(buff);
                cout << "Please input the absolute path to the csv file" << endl;
                string filePath;
                cin.ignore(INT_MAX, '\n');
                cin.clear();
                cin.sync();
                getline(cin, filePath);
                ifstream fileToRead(filePath);
                p.csvToTree(fileToRead);
                fileToRead.close();
                cout << "Please enter the absolute path to the author csv file" << endl;
                string authorPath;

                getline(cin, authorPath);

                ifstream authorToRead(authorPath);

                p.csvToHash(authorToRead);
                authorToRead.close();

                cout << "Loaded index" << endl;
                //Open file - Opens the CSV for quick access to the AVL tree
            } else if (UserInput == "4") {

                p.clearAvL();

                cout << "Cleared the index" << endl;
                //clearIndex(); //Don't have a function written out for this yet
            } else if (UserInput == "5") {
                cout << "What would you like to search for?" << endl;
                Query newQuery;
                string q;
                cin.ignore(INT_MAX, '\n');
                cin.clear();
                cin.sync();
                getline(cin, q);

                QueryProcessor queryProcessor;
                queryProcessor.setSearch(q);
                queryProcessor.genQuery();


                newQuery.setIn(queryProcessor.getQuery().getIn());
                newQuery.setAndQ(queryProcessor.getQuery().getAnd());
                newQuery.setOr(queryProcessor.getQuery().getOr());
                newQuery.setNot(queryProcessor.getQuery().getNot());
                newQuery.setAuthor(queryProcessor.getQuery().getAuthor());
                queryWords.push_back(newQuery.getIn());
                if (newQuery.hasAnd()) {
                    queryWords.push_back(newQuery.getAnd());
                }
                SearchEngine newSearch;
//                if(VectorOfJsons.empty()){
//                    newSearch.populateJsons(queryProcessor.getQuery(),p.getIndex(),file,stopWords,csvFile);
//                    VectorOfJsons = newSearch.getJsons();
//                }else{
//                    newSearch.setFiles(VectorOfJsons);
//                }
                //Clears the Result Vectors before doing new Search
                SearchResults.clear();
                topRankedArticles.clear();
                //This line pretty much takes List<string> and converts it to vector of string of unique ids and finds their object
                //THen I put it into SearchResults
                createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile));

                if(VectorOfJsons.empty()){

                    findObjects(createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile)),file,stopWords,csvFile);
                }else{
                    findObjects(createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile)), VectorOfJsons);
                }

                if (!SearchResults.empty()) {
                    bool run = true;
                    while (run) {
                        cout << endl << "Printing top 15 Articles:" << endl;
                        populateTopFiles();
                        printStats();
                        cout << "Choose an Option 1-" << topRankedArticles.size()
                             << " to see first 300 words or type 0 to EXIT" << endl;
                        int option;
                        cin >> option;
                        if (option <= topRankedArticles.size() && option > 0) {
                            option = option - 1;
                            printArticle(topRankedArticles.at(option).returnJsonFileName(), file);
                        } else if (option == 0) {
                            run = false;
                        } else {
                            cout << "Invalid Option. Please Try Again" << endl;
                        }
                    }
                } else {
                    cout << "No Search Results" << endl;
                }
            }else if (UserInput == "6") {
                cout << "What would you like to search for?" << endl;
                Query newQuery;
                string q;
                cin.ignore(INT_MAX, '\n');
                cin.clear();
                cin.sync();
                getline(cin, q);

                QueryProcessor queryProcessor;
                queryProcessor.setSearch(q);
                queryProcessor.genQuery();


                newQuery.setIn(queryProcessor.getQuery().getIn());
                newQuery.setAndQ(queryProcessor.getQuery().getAnd());
                newQuery.setOr(queryProcessor.getQuery().getOr());
                newQuery.setNot(queryProcessor.getQuery().getNot());
                newQuery.setAuthor(queryProcessor.getQuery().getAuthor());
                queryWords.push_back(newQuery.getIn());
                if (newQuery.hasAnd()) {
                    queryWords.push_back(newQuery.getAnd());
                }
                SearchEngine newSearch;
//                if(VectorOfJsons.empty()){
//                    newSearch.populateJsons(queryProcessor.getQuery(),p.getIndex(),file,stopWords,csvFile);
//                    VectorOfJsons = newSearch.getJsons();
//                }else{
//                    newSearch.setFiles(VectorOfJsons);
//                }
                //Clears the Result Vectors before doing new Search
                SearchResults.clear();
                topRankedArticles.clear();
                //This line pretty much takes List<string> and converts it to vector of string of unique ids and finds their object
                //THen I put it into SearchResults
                createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile));

                if(VectorOfJsons.empty()){

                    findObjects(createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile)),file,stopWords,csvFile);
                }else{
                    findObjects(createUniqueIds(newSearch.findDocs(newQuery,p.getIndex(),p.getHash(),file,stopWords,csvFile)), VectorOfJsons);
                }

                if (!SearchResults.empty()) {
                    bool run = true;
                    while (run) {
                        cout << endl << "Printing top 15 Articles:" << endl;
                        printStatsUnsorted();
                        cout << "Choose an Option 1-" << SearchResults.size()
                             << " to see first 300 words or type 0 to EXIT" << endl;
                        int option;
                        cin >> option;
                        if (option <= SearchResults.size() && option > 0) {
                            option = option - 1;
                            printArticle(SearchResults.at(option).returnJsonFileName(), file);
                        } else if (option == 0) {
                            run = false;
                        } else {
                            cout << "Invalid Option. Please Try Again" << endl;
                        }
                    }
                } else {
                    cout << "No Search Results" << endl;
                }
            }
            else if (UserInput == "7") {
                string option;
                cout << "Choose an Option" << endl << "~~~~~~~~~~~~~~~~~~~" << endl;
                cout
                        << "1.Total number of individual articles indexed\n2.Average number of words indexed per article\n3.Total number of unique words indexed\n4.Total number of unique Authors\nAnything Else To EXIT"
                        << endl;
                cin >> option;
                if (option == "1") {
                    cout << "Total Number of Articles Indexed: " << returnArticlesIndexed() << endl;
                } else if (option == "2") {
                    cout << "Average number of Words per Article: " << averageNumberOfWordsPerArticle() << endl;
                } else if (option == "3") {
                    long size = p.getIndex().returnSize();
                    setCount(size);
                    cout << "Number of Unique Words: " << returnUniqueWordsNumber() << endl;
                } else if (option == "4") {
                    cout << "Number of Unique Authors: " << returnUniqueAuthorsNumber() << endl;
                }  else {
                    cout << "Returning To Search Engine..." << endl << endl;
                }
            } else if (UserInput == "8") {
                cout << "Exiting Search Engine" << endl;
                RunUI = false;
            }
        } else {
            cout << "Invalid Option." << endl;
        }
    }
}


//Here's the function you wanted just put the things in and it will return the object
JsonObject UserInterface::findFile(string ID, const char *file, ifstream &stop, ifstream &csv) {
    DocParser newParse;
    JsonObject newObject = newParse.parseAFile(ID, file, stop, csv);

    return newObject;
}

void UserInterface::printArticle(string id, const char *file) {
    DocParser newParse;
    for (int i = 0; i < 300&&newParse.parse300Words(id,file).size(); i++) {
        if (newParse.parse300Words(id, file).at(i) == ".") {
            cout << newParse.parse300Words(id, file).at(i) << " ";
            cout << endl;
        } else {
            cout << newParse.parse300Words(id, file).at(i) << " ";
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

void UserInterface::populateTopFiles() {
    for (int i = 0; i < queryWords.size(); i++) {
        for (int j = 0; j < SearchResults.size(); j++) {
            SearchResults.at(j).startCount();
            for (int k = 0; k < SearchResults.at(j).returnText().size(); k++) {
                if (queryWords.at(i) == SearchResults.at(j).returnText().at(k)) {
                    SearchResults.at(j).increaseCount();
                }
            }
            countVector.push_back(SearchResults.at(j).returnCount());
        }
    }
    sort(countVector.begin(), countVector.end());
    for (int i = countVector.size()-1; i >= 0 && i>=countVector.size()-16; i--) {
        for (int j = 0; j < SearchResults.size(); j++) {
            if (countVector.at(i) == SearchResults.at(j).returnCount()) {
                topRankedArticles.push_back(SearchResults.at(j));
            }
        }
    }
}



void UserInterface::findObjects(vector<string> jsonIDS, const char *f, ifstream &stop, ifstream &csv) {
    for (auto &it:jsonIDS) {

        SearchResults.push_back(findFile(it, f, stop, csv));

    }
}


long UserInterface::returnArticlesIndexed() {
    return numberOfIndex;
}

long UserInterface::averageNumberOfWordsPerArticle() {
    long AVGWords = numberOfWords / numberOfIndex;
    return AVGWords;
}

void UserInterface::addAuthors(DocParser parse) {
    for (int i = 0; i < parse.getJsons().size(); i++) {
        for (int j = 0; j < parse.getJsons().at(i).returnAuthor().size(); j++) {
            Authors.insert(parse.getJsons().at(i).returnAuthor().at(j));
        }
    }
}

int UserInterface::returnUniqueAuthorsNumber() {
    return Authors.size();
}

void UserInterface::setCount(long Nodes) {
    sizeOfNode = Nodes;
}

long UserInterface::returnUniqueWordsNumber() {
    return sizeOfNode;
}

void UserInterface::printStats() {
    for (int i = 0; i < 15 && i < topRankedArticles.size(); i++) {
        if (topRankedArticles.at(i).returnTitle().empty()) {
            cout << i + 1 << ") Title: No Title" << endl;
        } else {
            cout << i + 1 << ") Title: " << topRankedArticles.at(i).returnTitle() << endl;
        }
        cout << "Author(s): ";
        for (int j = 0; j
                        < topRankedArticles.at(i).returnAuthor().size(); j++) {
            if (j != topRankedArticles.at(i).returnAuthor().size() - 1) {
                cout << topRankedArticles.at(i).returnAuthor().at(j) << ", ";
            } else {
                cout << topRankedArticles.at(i).returnAuthor().at(j);
            }
        }
        cout << endl;
        if (!topRankedArticles.at(i).returnPublisher().empty()) {
            cout << "Publisher: " << topRankedArticles.at(i).returnPublisher() << endl;
        } else {
            cout << "Unknown Publisher" << endl;
        }
        cout << "Publish Date: " << topRankedArticles.at(i).returnTime() << endl;
        cout << endl;
    }
}
void UserInterface::printStatsUnsorted() {
    for (int i = 0; i < 15 && i < SearchResults.size(); i++) {
        if (SearchResults.at(i).returnTitle().empty()) {
            cout << i + 1 << ") Title: No Title" << endl;
        } else {
            cout << i + 1 << ") Title: " << SearchResults.at(i).returnTitle() << endl;
        }
        cout << "Author(s): ";
        for (int j = 0; j
                        < SearchResults.at(i).returnAuthor().size(); j++) {
            if (j != SearchResults.at(i).returnAuthor().size() - 1) {
                cout << SearchResults.at(i).returnAuthor().at(j) << ", ";
            } else {
                cout << SearchResults.at(i).returnAuthor().at(j);
            }
        }
        cout << endl;
        if (!SearchResults.at(i).returnPublisher().empty()) {
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
    docParser.parseFiles(file, stopFile, csvFile);
    p.createIndex(docParser);
    //authorIndex=p.getAuthorIndex();
}

void UserInterface::clearIndex() {
    p.clearAvL();
}

void UserInterface::buildJsons() {

}

void UserInterface::findObjects(vector<string> jsonIDS, vector<JsonObject> allFiles) {
    for (int i = 0; i < jsonIDS.size(); i++) {
        for (int j = 0; j < allFiles.size(); j++) {
            if (allFiles.at(j).returnJsonFileName() == jsonIDS.at(i)) {
                SearchResults.push_back(allFiles.at(j));
            }
        }
    }
}

vector<string> UserInterface::returnMostCommonWords() {

}


