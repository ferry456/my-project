#ifndef __REINFORCEMENT_GEN_AGENT__H
#define __REINFORCEMENT_GEN_AGENT__H 

#include "enviro.h"
#include "styles.h"

using namespace enviro;
/*generate the equipment that could provide extra hp for palyers*/
class reinforcement_genController : public Process, public AgentInterface {

    public:
    reinforcement_genController() : Process(), AgentInterface() {}

    void init() {
        
    }
    void start() {
        timer = 0;
    }
    /*when and where the equipment would show up */
    void update() {
        timer++;
        if(timer == 60){
            Agent& reinforcement = add_agent("reinforcement",  rand()%400 - 200, 
                                            rand()%400 - 200,
                                            0,
                                            reinforcement_STYLE);   /*the equipment would randomly shows on the map*/  
        }
    }
    void stop() {}

    int timer;
};

class reinforcement_gen : public Agent {
    public:
    reinforcement_gen(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    reinforcement_genController c;
};

DECLARE_INTERFACE(reinforcement_gen)

#endif