FINAL_PROJECT
===

Overview
===
The goal of this project is to build a small game that could allow 2 people to play the tank fight in a same map and same screen.

The challenge I met when I was working on this project:
===
First of all the game should allow 2 players to paly at the same time by using the same screen same keyboard.

Secondly, After I finishing the demo of this game. I found that the players' tank could still lanch ammos after they were destoried by the other player.

At last, the problem that the equipments that randomly shows on the map which is hard to control and wont work if it was touched by players' tank.

Ways to solve the problems
===
I used 'esm generate player' to generate 2 players controller. Then, using the key bind method to make sure that the 2 different player could control its' own tank.
```bash
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
```
The boolean varible 'alive' controls the firing fuction whcih make sure the tank wont still fire bullets after destoried by other player.
```bash
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
```

By adding new reinforcement_gen could solve the reinforcement problem.
```bash
reinforcement_gen.json
reinforcement_gen.h
```

How to install and run the code
===
The first thing is to start the docker image environment, do
```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.1 bash
```
Then do
```bash
esm start
```
and then navigate to `http://localhost` 
Then do you should see a rectangular walled area and the 2 tanks.
```bash
make
enviro
```

The way to play the game
===
The dark black tank is controlled by 1P which uses 'w' 'a' 's' 'd' to move and the 'spacebar' is the firing buttom.

The grey tank is controlled by 2P which uses 'i' 'j' 'k' 'k' to move and the '0' is the firing buttom.

When a player got hitten by the bullets from other player their tank's hp would be reduced by 1. When one's hp comes to 0 the tanke would be destoried. The original hp for each player is 1 and the equipment(a blue cube) randomly shows on the map could change one's hp to 3 and it can only achieved by the first player that controls his tank to touch the equipment and after touched by player the equipment would disappear.

Future Works
===
Could add more equipemnts. For example, could add a bullets strenghten equipment that allows the palyer have higher damage or an equipment that could speed the palyer up.






All the sources the code uses
===
enviro, (https://github.com/klavinslab/enviro/tree/master/examples)

