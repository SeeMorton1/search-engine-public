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
                         const Value &metadata = d["metadata"];
//                         string title = metadata["title"].GetString();
//                         cout << title << endl;
                             if (metadata["authors"].IsObject()) {
                                     const Value &authors = metadata["authors"];
                                     string first = authors["first"].GetString();
                                     cout << first << endl;
                                     cout << "print" << endl;
                             }
                    }
                }
                fclose(fp);
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