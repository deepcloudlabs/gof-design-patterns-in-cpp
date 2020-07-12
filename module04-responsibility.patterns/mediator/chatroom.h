#pragma once

struct chat_room {
    vector<person *> people; // assume append-only

    void join(person *p);

    void broadcast(const string &origin, const string &message);

    void message(const string &origin, const string &who, const string &message);
};