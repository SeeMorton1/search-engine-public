//
// Created by Zihao Lin on 11/25/2020.
//

#include "UserInterface.h"
void UserInterface::startUI()
{
    cout << "Starting Search Engine" << endl;

    while (true)
    {

        cout << "What would you like to search for? Insert Close to exit the search engine." << endl;
        cin >> query;
        if (query == "Close" || query == "close"){
            break;
        }
        else{
            cout << "Searching...." << endl;
            addQuery(query);
        }
    }
}