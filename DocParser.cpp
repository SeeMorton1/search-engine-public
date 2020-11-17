//
// Created by zihao on 11/14/2020.
//

#include "DocParser.h"

int DocParser::parseFiles(const char *file) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(file)) != nullptr) {
        while ((ent = readdir(dir)) != nullptr) {
            string path = file;
            jsonfile = ent->d_name;
            path += "\\";
            path += jsonfile;
            const char *jsonPathing = path.c_str();


            FILE *fp = fopen(jsonPathing, "rb");
            char readBuffer[65536];
            FileReadStream is(fp, readBuffer, sizeof(readBuffer));

            Document d;
            d.ParseStream(is);

            if (d.IsObject()) {
                if (d.HasMember("metadata")) {
                    //Parses in Title
                    const Value &metadata = d["metadata"];
                    string title = metadata["title"].GetString();
                    cout << "-Title:" << endl;
                    cout << title << endl;

                    //Parsing in Authors
                    //https://github.com/Tencent/rapidjson/issues/1235
                    if (metadata["authors"].IsArray()) {
                        const Value &authors = metadata["authors"];
                        cout << "-Authors:" << endl;
                        for (rapidjson::Value::ConstValueIterator itr = authors.Begin(); itr != authors.End(); ++itr) {
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
                            cout << author << endl;
                        }
                    }
                }

                //Parsing in Abstract
                if (d.HasMember("abstract")) {
                    const Value &abstract = d["abstract"];
                    cout << "-Abstract:" << endl;
                    if (abstract.IsArray()) {
                        string abstractText;
                        for (rapidjson::Value::ConstValueIterator itr = abstract.Begin(); itr != abstract.End(); ++itr) {
                            const Value &attribute = *itr;
                            assert(attribute.IsObject());
                            for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();itr2 != attribute.MemberEnd(); ++itr2) {
                                if (attribute.HasMember("text")) {
                                    abstractText = attribute["text"].GetString();
                                }
                            }
                            cout << abstractText << endl;
                        }
                    }
                }
                
                //Parsing in BodyText
                if (d.HasMember("body_text")){
                    const Value& body_text = d["body_text"];
                    cout << "-Body:" << endl;
                    if (body_text.IsArray()){
                        string BodyText;
                        for (rapidjson::Value::ConstValueIterator itr = body_text.Begin(); itr != body_text.End(); ++itr) {
                            const Value &attribute = *itr;
                            assert(attribute.IsObject());
                            for (rapidjson::Value::ConstMemberIterator itr2 = attribute.MemberBegin();itr2 != attribute.MemberEnd(); ++itr2) {
                                if (attribute.HasMember("text")) {
                                    BodyText = attribute["text"].GetString();
                                }
                            }
                            cout << BodyText << endl;
                        }
                    }
                }
                cout << endl;
                fclose(fp);
            }
        }

        closedir(dir);
    } else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }
}


//int GetDir_Dirent(){
//    DIR *dir;
//
//    struct dirent *ent;
//    if ((dir = opendir ("cs2341_data")) != NULL) {
//        /* print all the files and directories within directory */
//        printf("List files using DIR:\n ");
//        while ((ent = readdir (dir)) != NULL) {
//            //printf ("%lu\n", ent->d_ino);
//            //printf("%s\n",ent->d_name);
//            std::string file = "cs2341_data/";
//
//            std::string s = ent->d_name;
//            file+=s;
//            const char *c = file.c_str();
//            FILE* fp = fopen(c,"rb");
//            char readBuffer[65536];
//            FileReadStream is(fp,readBuffer,sizeof(readBuffer));
//            Document doc;
//            doc.ParseStream(is);
//            if(doc.IsObject()){
//                if(doc.HasMember("metadata")){
//                    std::cout<<"Has metadata\n";
//                    if(doc["metadata"].IsObject()) {
//
//                        Value &meta = doc["metadata"];
//
//                        for (auto &item:meta.GetObject()) {
//
//                            std::cout << item.name.GetString() << std::endl;
//                        }
//                    }
//
//                    if(doc["metadata"].HasMember("authors")){
//                        std::cout<<"Has authors\n\n";
//
//                    }
//                }
//            }
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }
//}