//
//  toolkit.h
//  gismo
//
//  Created by isana137 on 12/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gismo_toolkit_h
#define gismo_toolkit_h

#define MOV_FIX 1.0
#define RANDOM_WALK_FIX 1.0

#include <math.h>
#include "slEuclid.h"



//enum for interaction mode
typedef enum interaction_mode {RANDOM_WALK, CHASE, RUN, ATTACK, DMG, DEATH} interaction_mode;


class ToolKit {

public:
    ToolKit();
    int dice(unsigned int num); //Random Generator with dice model
    unsigned long generateUniqueID(); //Create unique ID for Seed
    sl_scaled_position randomizePosition();
    sl_scaled_position move(interaction_mode mode, float mov, sl_scaled_position here, sl_scaled_position target);
    
private:
    unsigned int id_counter;
    unsigned long pre_id;

};

#endif
