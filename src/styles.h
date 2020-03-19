#ifndef __STYLES__H
#define __STYLES__H

#include "enviro.h"

using namespace enviro;

const json  BULLET1_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "2px"},
                   {"strokeOpacity", "0.25"}
            },
            BULLET2_STYLE = { 
                   {"fill", "red"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "2px"},
                   {"strokeOpacity", "0.25"}
            },
            
            PLAYER1_FRAGMENT_STYLE = { 
                {"fill", "orange"}, 
                {"stroke", "black"}, 
                {"strokeWidth", "5px"},
                {"strokeOpacity", "0.25"}
            },
            PLAYER2_FRAGMENT_STYLE = { 
                {"fill", "orange"}, 
                {"stroke", "black"}, 
                {"strokeWidth", "5px"},
                {"strokeOpacity", "0.25"}
            },

            POWERUP1_STYLE = { 
                {"fill", "orange"}, 
                {"stroke", "black"}, 
                {"strokeWidth", "5px"},
                {"strokeOpacity", "0.25"}
            },
            POWERUP2_STYLE = { 
                {"fill", "orange"}, 
                {"stroke", "black"}, 
                {"strokeWidth", "5px"},
                {"strokeOpacity", "0.25"}
            },

            reinforcement_STYLE = { 
                   {"fill", "blue"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "2px"},
                   {"strokeOpacity", "0.25"}
            };


#endif