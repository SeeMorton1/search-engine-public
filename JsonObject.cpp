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
    wordCount = copy.wordCount;
}

void JsonObject::addText(const string& t) {
    wordCount++;
    text.push_back(t);
}

void JsonObject::addAuthors(const string& author) {
    authors.push_back(author);
}

void JsonObject::jsonFileNameSet(string json) {
    jsonFileName = json;
}

void JsonObject::setWordCount(int x) {
    wordCount = x;
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

int JsonObject::returnWordCount() {
    return wordCount;
}

void JsonObject::setTitle(const string &t) {
    title = t;
}