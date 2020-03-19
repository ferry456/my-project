#ifndef __PLAYER2FRAGMENT_AGENT__H
#define __PLAYER2FRAGMENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class player2fragmentController : public Process, public AgentInterface {

    public:
    player2fragmentController() : Process(), AgentInterface() {}

    void init() {
        counter = rand() % 8;
    }
    void start() {}
    void update() {
        if ( counter-- <= 0 ) {
            remove_agent(id());
        }
    }
    void stop() {}
    int counter;
    const int fmax = 10;

};

class player2fragment : public Agent {
    public:
    player2fragment(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    player2fragmentController c;
};

DECLARE_INTERFACE(player2fragment)

#endif