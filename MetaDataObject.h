//
// Created by zihao on 12/1/2020.
//

#ifndef SEARCH_ENGINE_LIN_MORTON_METADATAOBJECT_H
#define SEARCH_ENGINE_LIN_MORTON_METADATAOBJECT_H
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

class MetaDataObject {
private:
    string ID;
    bool fullText;
    string publisher;
    string publishtime;
public:

    MetaDataObject();
    MetaDataObject(const MetaDataObject& copy);
    ~MetaDataObject();

    void setID(string id);
    void checkFullText(string text);
    void setPublisher(string publish);
    void setTime(string date);

    string returnID();
    bool returnFullText();
    string returnPublisher();
    string returnPublishTime();

};


#endif //SEARCH_ENGINE_LIN_MORTON_METADATAOBJECT_H
