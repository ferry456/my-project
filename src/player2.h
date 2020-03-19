#ifndef __PLAYER2_AGENT__H
#define __PLAYER2_AGENT__H 

#include "enviro.h"
#include "styles.h"

using namespace enviro;

class Player2Controller : public Process, public AgentInterface {

    public:
    Player2Controller() : Process(), AgentInterface(), v(0), omega(0), firing2(false), alive(true),hp(1) {}

    void init() {
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "0" && !firing2 && alive) {
                  Agent& bullet2 = add_agent("Bullet2", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    BULLET2_STYLE);    
                    bullet2.apply_force(100,0);
                  firing2 = true;
            } else if ( k == "i" ) {
                  v = v_m;              
            } else if ( k == "k" ) {
                  v = -v_m;  
            } else if ( k == "j" ) {
                  omega = -omega_m;
            } else if ( k == "l" ) {
                  omega = omega_m;
            } 
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "0" ) {
                firing2 = false;
            } else if ( k == "i" || k == "k" ) {
                  v = 0;               
            } else if ( k == "j" ) {
                  omega = 0;
            } else if ( k == "l" ) {
                  omega = 0;
            } 
        });

        notice_collisions_with("Bullet1", [&](Event &e) {
            hp--;
        });


        notice_collisions_with("reinforcement", [&](Event& e) {
            remove_agent(e.value()["id"]);
            hp = 3;
        });

    }
    void start() { }

    void doom1() {
        alive = false;
        for ( double theta=0; theta < 2 * M_PI; theta += M_PI / 4) {
            Agent& frag = add_agent("player2fragment", x(), y(), theta, PLAYER2_FRAGMENT_STYLE);
            frag.omni_apply_force(
                50*cos(theta+M_PI/8) + vx, 
                50*sin(theta+M_PI/8) + vy
            );
        }  
        remove_agent(id());
    }

    void update() {
        track_velocity(v,omega,10,400);
        //center(x(), y());
        if(hp <= 0){
            doom1();
        }
    }
    void stop() {}

    bool hit;
    double vx, vy;
    double v, omega;
    double const v_m = 30, omega_m = 1;
    bool firing2;
    bool alive;
    int hp;

};

class Player2 : public Agent {
    public:
    Player2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    Player2Controller c;
};

DECLARE_INTERFACE(Player2)

#endif