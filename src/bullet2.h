#ifndef __BULLET2_AGENT__H
#define __BULLET2_AGENT__H 

#include "enviro.h"

using namespace enviro;

class Bullet2Controller : public Process, public AgentInterface {

    public:
    Bullet2Controller() : Process(), AgentInterface(), counter(0) {}

    void init() {
        notice_collisions_with("player1", [&](Event &e) {
            remove_agent(id());
        });               
    }

    void start() {}

    void update() {
        if ( counter++ > 12 ) {
            remove_agent(id());
        }
     }
    void stop() {}

    double counter;

};

class Bullet2 : public Agent {
    public:
    Bullet2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    Bullet2Controller c;
};

DECLARE_INTERFACE(Bullet2)

#endif