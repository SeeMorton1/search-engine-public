//
// Created by zihao on 11/17/2020.
//

#include "JsonObject.h"

JsonObject::JsonObject() = default;

JsonObject::~JsonObject() = default;

JsonObject::JsonObject(const JsonObject &copy) {
    text = copy.text;
    authors = copy.authors;
    jsonFileName = copy.jsonFileName;
    title = copy.title;
    publisher = copy.publisher;
    publishTime = copy.publishTime;
    count = copy.count;
}

void JsonObject::startCount() {
    count = 0;
}
void JsonObject::increaseCount() {
    count++;
}

void JsonObject::addText(const string& t) {
    text.push_back(t);
}

void JsonObject::addAuthors(const string& author) {
    authors.push_back(author);
}

void JsonObject::jsonFileNameSet(string json) {
    jsonFileName = json;
}

vector<string> JsonObject::returnAuthor() {
    return authors;
}

vector<string> JsonObject::returnText() {
    return text;
}

string JsonObject::returnJsonFileName() {
    return jsonFileName;
}

void JsonObject::setTitle(const string& t) {
    title = t;
}

void JsonObject::setPublisher(const string& p) {
    publisher = p;
}
void JsonObject::setPublishTime(const string& t) {
    publishTime = t;
}
string JsonObject::returnTitle() {
    return title;
}
string JsonObject::returnTime() {
    return publishTime;
}
string JsonObject::returnPublisher() {
    return publisher;
}
int JsonObject::returnCount() {
    return count;
}