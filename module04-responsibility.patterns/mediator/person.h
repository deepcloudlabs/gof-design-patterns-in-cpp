#pragma once

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct chat_room;

struct person {
    string name;
    chat_room *room = nullptr;

    person(const string &name);

    void receive(const string &origin, const string &message);

    void say(const string &message) const;

    vector<string> chat_log;

    void pm(const string &who, const string &message) const;

    friend bool operator==(const person &lhs, const person &rhs) {
        return lhs.name == rhs.name;
    }

    friend bool operator!=(const person &lhs, const person &rhs) {
        return !(lhs == rhs);
    }
};