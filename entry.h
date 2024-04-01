//
// Created by denys on 12.03.24.
//

#ifndef LEARNING_ENTRY_H
#define LEARNING_ENTRY_H

#include "string"
#include "ctime"

using namespace std;

class Entry {
protected:
    string date;
    time_t creationTime;
    string type = "";
public:
    Entry(){};
    Entry(string _title) {
        time_t now = time(0);
        title = _title,
        date = ctime(&now),
        creationTime = now;
    }

    string getType() {
        return type;
    }

    time_t getTime() {
        return creationTime;
    }

    string getDate() {
        return date;
    }


    string title;
    string text;
    string name;
    string surname;
    string notes;
    string description;
    string fromToTime;
    string location;
};

class Accident : public Entry {
public:
    Accident(string _title) : Entry(_title) { type = "Event"; }

    Accident(string _title, string _fromToTime,
             string _description, string _location) : Entry(_title) {
        fromToTime = _fromToTime;
        description = _description;
        location = _location;
        type = "Event";
    }
};

class Note : public Entry {
public:
    Note(string title) : Entry(title) { type = "Note"; }

    Note(string _title, string _text) : Entry(_title) {
        text = _text;
        type = "Note";
    }

};

class Contact : public Entry {
public:
    Contact(string _title) : Entry(_title) {
        type = "Contact";
    }

    Contact(string _title, string _name, string _surname, string _notes) : Entry(_title) {
        name = _name;
        surname = _surname;
        notes = _notes;
        type = "Contact";
    }
};

#endif //LEARNING_ENTRY_H
