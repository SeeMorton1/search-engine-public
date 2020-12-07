//
// Created by zihao on 11/14/2020.
//

#include "DocParser.h"

DocParser::DocParser() = default;

DocParser::~DocParser() = default;

DocParser::DocParser(const DocParser &copy) {
    author = copy.author;
    text = copy.text;
    jsonfile = copy.jsonfile;
    vectorOfMetaData = copy.vectorOfMetaData;
    vectorOfJson = copy.vectorOfJson;
    stopWords = copy.stopWords;
}

int DocParser::parseFiles(const char *file, ifstream &stop, ifstream &csv) {
    readInStopWords(stop);
    parseMetaData(csv);
    std::ifstream in{"diffs.txt"};
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(file)) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            bool FullText = false;
            string date;
            string publisher;
            string path = file;
            jsonfile = ent->d_name;
            path += "/";
            path += jsonfile;
            const char *jsonPathing = path.c_str();
            for (int i = 0; i < vectorOfMetaData.size(); i++) {
                if (jsonfile == vectorOfMetaData.at(i).returnID()) {
                    if (vectorOfMetaData.at(i).returnFullText()) {
                        FullText = true;
                        date = vectorOfMetaData.at(i).returnPublishTime();
                        publisher = vectorOfMetaData.at(i).returnPublisher();
                    }
                }
            }

            if (FullText) {
                FILE *fp = fopen(jsonPathing, "rb");
                char readBuffer[65536];
                FileReadStream is(fp, readBuffer, sizeof(readBuffer));

                Document d;
                d.ParseStream(is);


                //Object for Json Class
                JsonObject newObject;
                newObject.jsonFileNameSet(jsonfile);

                if (d.IsObject()) {
                    if (d.HasMember("metadata")) {
                        //Parses in Title
                        const Value &metadata = d["metadata"];
                        string title = metadata["title"].GetString();
                        newObject.setTitle(title);


                        //Parsing in Authors
                        //https://github.com/Tencent/rapidjson/issues/1235
                        if (metadata["authors"].IsArray()) {
                            const Value &authors = metadata["authors"];
                            //cout << "-Authors:" << endl;
                            for (rapidjson::Value::ConstValueIterator itr = authors.Begin();
                                 itr != authors.End(); ++itr) {
                                const Value &attribute = *itr;
                                assert(attribute.IsObject());
                                for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
                                     itr2 != attribute.MemberEnd(); ++itr2) {
                                    if (attribute.HasMember("first")) {
                                        author = attribute["first"].GetString();
                                        author += " ";
                                        author += attribute["last"].GetString();
                                    }
                                }
                                newObject.addAuthors(author);
                            }
                        }
                    }

                    //Parsing in Abstract
//                if (d.HasMember("abstract")) {
//                    const Value &abstract = d["abstract"];
//                    //cout << "-Abstract:" << endl;
//                    if (abstract.IsArray()) {
//                        string abstractText;
//                        for (rapidjson::Value::ConstValueIterator itr = abstract.Begin();
//                             itr != abstract.End(); ++itr) {
//                            const Value &attribute = *itr;
//                            assert(attribute.IsObject());
//                            for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
//                                 itr2 != attribute.MemberEnd(); ++itr2) {
//                                if (attribute.HasMember("text")) {
//                                    abstractText = attribute["text"].GetString();
//                                }
//                            }
//
//                            string word = "";
//                            for (auto x:abstractText) {
//                                transform(word.begin(), word.end(), word.begin(), ::tolower);
//                                if (x == ' ') {
//                                    if (word.size() > 1) {
//                                        Porter2Stemmer::stem(word);
//                                        newObject.addText(word);
//                                        word = "";
//                                    }
//                                } else if ((x<33 || x>47) && (x>64 || x <58)){
//                                    word = word + x;
//                                }
//                            }
//                        }
//                    }
//                }

                    //Parsing in BodyText
                    if (d.HasMember("body_text")) {
                        const Value &body_text = d["body_text"];
                        //cout << "-Body:" << endl;
                        if (body_text.IsArray()) {
                            string BodyText;
                            for (rapidjson::Value::ConstValueIterator itr = body_text.Begin();
                                 itr != body_text.End(); ++itr) {
                                const Value &attribute = *itr;
                                if (attribute.HasMember("text")) {
                                    BodyText = attribute["text"].GetString();
                                }
                                string word = "";
                                for (auto x:BodyText) {
                                    transform(word.begin(), word.end(), word.begin(), ::tolower);
                                    if (x == ' ') {
                                        if (word.size() > 1) {
                                            if (!stopWords.isFound(word)) {
                                                Porter2Stemmer::stem(word);
                                                newObject.addText(word);
                                            }
                                            word = "";
                                        }
                                    } else if ((x > 47 && x < 58) || (x > 64 && x < 91) || (x > 96 && x < 123) ||
                                               (x == '-')) {
                                        word = word + x;
                                    }
                                }
                            }
                        }
                    }
                    newObject.setPublisher(publisher);
                    newObject.setPublishTime(date);
                    vectorOfJson.push_back(newObject);
                    fclose(fp);
                }
            }
        }
        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
}

JsonObject DocParser::parseAFile(string ID, const char *file,ifstream &stop, ifstream &csv) {
    readInStopWords(stop);
    parseMetaData(csv);
    std::ifstream in{"diffs.txt"};
    bool FullText = false;
    string date;
    string publisher;
    string path = file;
    path += "/";
    path += ID;
    const char *jsonPathing = path.c_str();
    for (int i = 0; i < vectorOfMetaData.size(); i++) {
        if (ID == vectorOfMetaData.at(i).returnID()) {

            FullText = true;
            date = vectorOfMetaData.at(i).returnPublishTime();
            publisher = vectorOfMetaData.at(i).returnPublisher();

        }
    }


    JsonObject newObject;
    FILE *fp = fopen(jsonPathing, "rb");
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);
    //Object for Json Class
    newObject.jsonFileNameSet(ID);

    if (d.IsObject()) {
        if (d.HasMember("metadata")) {
            //Parses in Title
            const Value &metadata = d["metadata"];
            string title = metadata["title"].GetString();
            newObject.setTitle(title);


            //Parsing in Authors
            //https://github.com/Tencent/rapidjson/issues/1235
            if (metadata["authors"].IsArray()) {
                const Value &authors = metadata["authors"];
                //cout << "-Authors:" << endl;
                for (rapidjson::Value::ConstValueIterator itr = authors.Begin();
                     itr != authors.End(); ++itr) {
                    const Value &attribute = *itr;
                    assert(attribute.IsObject());
                    for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
                         itr2 != attribute.MemberEnd(); ++itr2) {
                        if (attribute.HasMember("first")) {
                            author = attribute["first"].GetString();
                            author += " ";
                            author += attribute["last"].GetString();
                        }
                    }
                    newObject.addAuthors(author);
                }
            }
        }

        //Parsing in Abstract
//                if (d.HasMember("abstract")) {
//                    const Value &abstract = d["abstract"];
//                    //cout << "-Abstract:" << endl;
//                    if (abstract.IsArray()) {
//                        string abstractText;
//                        for (rapidjson::Value::ConstValueIterator itr = abstract.Begin();
//                             itr != abstract.End(); ++itr) {
//                            const Value &attribute = *itr;
//                            assert(attribute.IsObject());
//                            for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();
//                                 itr2 != attribute.MemberEnd(); ++itr2) {
//                                if (attribute.HasMember("text")) {
//                                    abstractText = attribute["text"].GetString();
//                                }
//                            }
//
//                            string word = "";
//                            for (auto x:abstractText) {
//                                transform(word.begin(), word.end(), word.begin(), ::tolower);
//                                if (x == ' ') {
//                                    if (word.size() > 1) {
//                                        Porter2Stemmer::stem(word);
//                                        newObject.addText(word);
//                                        word = "";
//                                    }
//                                } else if ((x<33 || x>47) && (x>64 || x <58)){
//                                    word = word + x;
//                                }
//                            }
//                        }
//                    }
//                }

        //Parsing in BodyText
        if (d.HasMember("body_text")) {
            const Value &body_text = d["body_text"];
            //cout << "-Body:" << endl;
            if (body_text.IsArray()) {
                string BodyText;
                for (rapidjson::Value::ConstValueIterator itr = body_text.Begin();
                     itr != body_text.End(); ++itr) {
                    const Value &attribute = *itr;
                    if (attribute.HasMember("text")) {
                        BodyText = attribute["text"].GetString();
                    }
                    string word = "";
                    for (auto x:BodyText) {
                        transform(word.begin(), word.end(), word.begin(), ::tolower);
                        if (x == ' ') {
                            if (word.size() > 1) {
                                if (!stopWords.isFound(word)) {
                                    Porter2Stemmer::stem(word);
                                    newObject.addText(word);
                                }
                                word = "";
                            }
                        } else if ((x > 47 && x < 58) || (x > 64 && x < 91) || (x > 96 && x < 123) || (x == '-')) {
                            word = word + x;
                        }
                    }
                }
            }
        }
        newObject.setPublisher(publisher);
        newObject.setPublishTime(date);
        fclose(fp);

        return newObject;
    }

}

vector<string> DocParser::parse300Words(string ID, const char *file) {
    string path = file;
    path += "/";
    path += ID;
    const char *jsonPathing = path.c_str();
    FILE *fp = fopen(jsonPathing, "rb");
    char readBuffer[65536];
    FileReadStream is(fp, readBuffer, sizeof(readBuffer));

    Document d;
    d.ParseStream(is);
    //Object for Json Class
    JsonObject newObject;
    if (d.HasMember("body_text")) {
        const Value &body_text = d["body_text"];
        //cout << "-Body:" << endl;
        if (body_text.IsArray()) {
            string BodyText;
            for (rapidjson::Value::ConstValueIterator itr = body_text.Begin();
                 itr != body_text.End(); ++itr) {
                const Value &attribute = *itr;
                if (attribute.HasMember("text")) {
                    BodyText = attribute["text"].GetString();
                }
                string word = "";
                for (auto x:BodyText) {
                    if (x == ' ') {
                        newObject.addText(word);
                        word = "";
                    } else {
                        word = word + x;
                    }
                }
            }
        }
    }
    return newObject.returnText();
}


    void DocParser::parseMetaData(ifstream &csv) {
        if (csv.is_open()) {
            rapidcsv::Document doc(csv);
            vector<string> sha = doc.GetColumn<string>("sha");
            vector<string> publish_time = doc.GetColumn<string>("publish_time");
            vector<string> journal = doc.GetColumn<string>("journal");
            vector<string> full_text_file = doc.GetColumn<string>("has_pdf_parse");

            for (int i = 0; i < sha.size(); i++) {
                MetaDataObject newLine;
                string Id = sha.at(i);
                Id += ".json";
                newLine.setID(Id);
                newLine.setPublisher(journal.at(i));
                newLine.setTime(publish_time.at(i));
                newLine.checkFullText(full_text_file.at(i));
//        if (newLine.returnFullText()){
//            cout << "True" << endl;
//        }
//        else{
//            cout << "False" << endl;
//        }
                vectorOfMetaData.push_back(newLine);
            }

        } else {
            cout << "No CSV File" << endl;
        }
        csv.close();
    }

    vector<MetaDataObject> DocParser::getMeta() {
        return vectorOfMetaData;
    }

    vector<JsonObject> DocParser::getJsons() {
        return vectorOfJson;
    }

    void DocParser::printAuthor() {
        for (int i = 0; i < vectorOfJson.size(); i++) {
            cout << "-Next File " << endl;
            for (int j = 0; j < vectorOfJson.at(i).returnAuthor().size(); j++) {
                cout << vectorOfJson.at(i).returnAuthor().at(j) << endl;
            }
            cout << endl;
        }
    }

    void DocParser::printjsonfile() {
        for (int i = 0; i < vectorOfJson.size(); i++) {
            cout << "-Json" << endl;
            cout << vectorOfJson.at(i).returnJsonFileName() << endl;
        }
    }

    void DocParser::printText() {
        for (int i = 0; i < vectorOfJson.size(); i++) {
            cout << "-Text " << endl;
            for (int j = 0; j < vectorOfJson.at(i).returnText().size(); j++) {
                cout << vectorOfJson.at(i).returnText().at(j) << endl;
            }
            cout << endl;
        }
    }

    void DocParser::readInStopWords(ifstream &file) {
        string words;
        if (file.is_open()) {
            while (!file.eof()) {
                getline(file, words);
                stopWords.insert(words);
            }
        } else {
            cout << "No StopWords File" << endl;
        }
        file.close();
    }

