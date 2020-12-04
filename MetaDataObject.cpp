//
// Created by zihao on 12/1/2020.
//

#include "MetaDataObject.h"

MetaDataObject::MetaDataObject()=default;
MetaDataObject::~MetaDataObject()= default;
MetaDataObject::MetaDataObject(const MetaDataObject &copy) {
    ID = copy.ID;
    fullText = copy.fullText;
    publisher = copy.publisher;
    publishtime = copy.publishtime;
}

void MetaDataObject::setID(string id) {
    ID = id;
}

void MetaDataObject::checkFullText(string text) {
    if (text[0] == 'T'){
        fullText = true;
    }
    else{
        fullText = false;
    }
}

void MetaDataObject::setPublisher(string publish) {
    publisher = publish;
}

void MetaDataObject::setTime(string date) {
    publishtime = date;
}

string MetaDataObject::returnID() {
    return ID;
}

bool MetaDataObject::returnFullText() const {
    return fullText;
}

string MetaDataObject::returnPublisher() {
    return publisher;
}

string MetaDataObject::returnPublishTime() {
    return publishtime;
}
