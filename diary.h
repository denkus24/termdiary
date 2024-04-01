//
// Created by denys on 12.03.24.
//

#ifndef LEARNING_DIARY_H
#define LEARNING_DIARY_H

#include <fstream>
#include <dirent.h>
#include <sstream>
#include "iostream"
#include "entry.h"
#include <string>
#include <vector>
#include "json/single_include/nlohmann/json.hpp"
#include <cstdio>

using json = nlohmann::json;
namespace fs = std::filesystem;
using namespace std;

class Diary {
private:
    vector<Entry> entries;
    vector<std::string> entriesPaths;
public:
    Diary() {

        std::string path = "../entries";

        for (const auto &entry: fs::directory_iterator(path)) {
            entriesPaths.push_back(entry.path().string());

            std::ifstream file(entry.path().string(), std::ifstream::binary);
            json js = json::parse(file);
            std::string type = js["type"];

            if (type == "note") {
                Note newNote = Note(js["title"], js["text"]);
                entries.push_back(newNote);
            } else if (type == "event") {
                Accident newAccident = Accident(js["title"],
                                                js["time"],
                                                js["description"],
                                                js["location"]);
                entries.push_back(newAccident);
            } else if (type == "contact") {
                Contact newContact = Contact(js["title"], js["name"], js["surname"], js["notes"]);
                entries.push_back(newContact);
            }
        }
    }

    void addNewEntry(Entry newEntry) {
        entries.push_back(newEntry);

        //Writing to file
        string type = newEntry.getType();
        string filename = "../entries/" + to_string(newEntry.getTime()) + ".json";
        json writeInformation;

        if (type == "Note") {
            writeInformation["title"] = newEntry.title;
            writeInformation["type"] = "note";
            writeInformation["text"] = newEntry.text;
        } else if (type == "Contact") {
            writeInformation["title"] = newEntry.title;
            writeInformation["type"] = "contact";
            writeInformation["name"] = newEntry.name;
            writeInformation["surname"] = newEntry.surname;
            writeInformation["notes"] = newEntry.notes;
        } else {
            writeInformation["title"] = newEntry.title;
            writeInformation["type"] = "event";
            writeInformation["time"] = newEntry.fromToTime;
            writeInformation["location"] = newEntry.location;
            writeInformation["description"] = newEntry.description;
        }
        ofstream file(filename);
        if (file.is_open()) {
            file << writeInformation;
            file.close();
        } else {
            std::cout << "error";
        }
        entriesPaths.push_back(filename);
        entries.push_back(newEntry);

    }

    void deleteEntry(const int &entryIndex) {
        fs::remove(entriesPaths[entryIndex]);
        entriesPaths.erase(next(entriesPaths.begin(), entryIndex));
        entries.erase(next(entries.begin(), entryIndex));
    }

    void entryUpdate(Entry oldEntry, Entry newEntry, const int &index) {
        string type = oldEntry.getType();
        json writeJson;

        if (type == "Note") {
            writeJson["title"] = newEntry.title;
            writeJson["type"] = "note";
            writeJson["text"] = newEntry.text;
        } else if (type == "Event") {
            writeJson["title"] = newEntry.title;
            writeJson["type"] = "event";
            writeJson["time"] = newEntry.fromToTime;
            writeJson["description"] = newEntry.description;
            writeJson["location"] = newEntry.location;
        } else if (type == "Contact") {
            writeJson["title"] = newEntry.title;
            writeJson["type"] = "contact";
            writeJson["name"] = newEntry.name;
            writeJson["surname"] = newEntry.surname;
            writeJson["notes"] = newEntry.notes;
        }

        ofstream file(entriesPaths[index]);
        if (file.is_open()) {
            file << writeJson;
            file.close();
        }


    }

    vector<Entry> getEntries() {
        return entries;
    }
};

#endif //LEARNING_DIARY_H
