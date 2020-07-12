#include "person.h"
#include "chatroom.h"
#include <algorithm>

void chat_room::broadcast(const string &origin, const string &message) {
    for (auto p : people)
        if (p->name != origin)
            p->receive(origin, message);
}

void chat_room::join(person *p) {
    string join_msg = p->name + " joins the chat";
    broadcast("room", join_msg);

    p->room = this;
    people.push_back(p);
}

void chat_room::message(const string &origin, const string &who, const string &message) {
    auto target = find_if(begin(people), end(people), [&](const person *p) { return p->name == who; });
    if (target != end(people)) {
        (*target)->receive(origin, message);
    }
}