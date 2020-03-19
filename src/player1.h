#ifndef __PLAYER1_AGENT__H
#define __PLAYER1_AGENT__H 

#include "styles.h"
#include "enviro.h"
#include <math.h>


using namespace enviro;

class player1Controller : public Process, public AgentInterface {

    public:
    player1Controller() : Process(), AgentInterface(), hit(false), power(false),timer(0), alive(true), hp(1), re(false) {}

    void init() {
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " && !firing1 && alive) {
                  Agent& bullet1 = add_agent("Bullet1", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    BULLET1_STYLE);    
                    bullet1.apply_force(100,0);
                  firing1 = true;
            } else if ( k == "w" ) {
                  v = v_m;              
            } else if ( k == "s" ) {
                  v = -v_m;  
            } else if ( k == "a" ) {
                  omega = -omega_m;
            } else if ( k == "d" ) {
                  omega = omega_m;
            } 
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " ) {
                firing1 = false;
            } else if ( k == "w" || k == "s" ) {
                  v = 0;               
            } else if ( k == "a" ) {
                  omega = 0;
            } else if ( k == "d" ) {
                  omega = 0;
            } 
        });

        notice_collisions_with("Bullet2", [&](Event &e) {
            hp--;
        });

        // notice_collisions_with("M_Bullet", [&](Event &e) {
        //     hp = hp - 2;
        // });

        notice_collisions_with("reinforcement", [&](Event &e) {
            remove_agent(e.value()["id"]);
            // Agent& powerup = find_agent(e.value()["id"]);
            hp = 3;
        });

        // notice_collisions_with("reinforcement1", [&](Event &e) {
        //     alive = false;
        //     re = true;
        //     remove_agent(e.value()["id"]);
        // });
    }
    void start() {}

    void doom() {
        alive = false;
        //re = false;
        for ( double theta=0; theta < 2 * M_PI; theta += M_PI / 4) {
            Agent& frag = add_agent("player1fragment", x(), y(), theta, PLAYER1_FRAGMENT_STYLE);
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
            doom();
        }
        /*if (re){
            watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " && !firing1 && re) {
                  Agent& bullet1 = add_agent("M_Bullet", 
                    x() + 17*cos(angle()), 
                    y() + 17*sin(angle()), 
                    angle(), 
                    M_BULLET_STYLE);    
                    M_bullet.apply_force(100,0);
                  firing1 = true;
            } else if ( k == "w" ) {
                  v = v_m;              
            } else if ( k == "s" ) {
                  v = -v_m;  
            } else if ( k == "a" ) {
                  omega = -omega_m;
            } else if ( k == "d" ) {
                  omega = omega_m;
            }
            watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == " " ) {
                firing1 = false;
            } else if ( k == "w" || k == "s" ) {
                  v = 0;               
            } else if ( k == "a" ) {
                  omega = 0;
            } else if ( k == "d" ) {
                  omega = 0;
            }

        }*/
        
    }
    void stop() {}

    bool hit;
    double vx, vy;
    double v, omega;
    double const v_m = 30, omega_m = 1;
    bool firing1;
    bool power;
    int timer;
    bool alive;
    bool re;
    int hp;
};

class player1 : public Agent {
    public:
    player1(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    player1Controller c;
};

DECLARE_INTERFACE(player1)

#endif