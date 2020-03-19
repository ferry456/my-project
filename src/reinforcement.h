#ifndef __REINFORCEMENT_AGENT__H
#define __REINFORCEMENT_AGENT__H 

#include "enviro.h"

using namespace enviro;

class reinforcementController : public Process, public AgentInterface {

    public:
    reinforcementController() : Process(), AgentInterface(), consumed(false){}

    void init() {
        notice_collisions_with("player1", [&](Event& e) {
            remove_agent(id());
        });

        notice_collisions_with("player2", [&](Event& e) {
            remove_agent(id());
        });
    }
    void start() {}
    void update() {
    }
    void stop() {}

    bool consumed;
};

class reinforcement : public Agent {
    public:
    reinforcement(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }

    private:
    reinforcementController c;
};

DECLARE_INTERFACE(reinforcement)

#endif