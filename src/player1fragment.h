#ifndef __PLAYER1FRAGMENT_AGENT__H
#define __PLAYER1FRAGMENT_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

class player1fragmentController : public Process, public AgentInterface {

    public:
    player1fragmentController() : Process(), AgentInterface() {}

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

class player1fragment : public Agent {
    public:
    player1fragment(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    player1fragmentController c;
};

DECLARE_INTERFACE(player1fragment)

#endif