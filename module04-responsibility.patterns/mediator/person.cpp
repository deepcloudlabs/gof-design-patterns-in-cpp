#include "person.h"
#include "chatroom.h"

person::person(const string &name) : name(name) {
}

void person::receive(const string &origin, const string &message) {
    string s{origin + ": \"" + message + "\""};
    cout << "[" << name << "'s chat session] " << s << "\n";
    chat_log.emplace_back(s);
}

void person::say(const string &message) const {
    room->broadcast(name, message);
}

void person::pm(const string &who, const string &message) const {
    room->message(name, who, message);
}