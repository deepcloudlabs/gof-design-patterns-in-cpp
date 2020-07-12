#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "person.h"
#include "chatroom.h"

int main() {
    chat_room room;

    person jack{"jack"};
    person kate{"kate"};
    room.join(&jack);
    room.join(&kate);
    jack.say("hi room");
    kate.say("oh, hey jack");

    person james("james");
    room.join(&james);
    james.say("hi everyone!");

    kate.pm("simon", "glad you could join us, james");

    return 0;
}