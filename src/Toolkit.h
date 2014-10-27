//
//  toolkit.h
//  gismo
//
//  Created by isana137 on 12/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gismo_toolkit_h
#define gismo_toolkit_h


#include <math.h>
#include "slEuclid.h"
#include "slCellModelSetup.h"



class ToolKit {

public:
    ToolKit();
    int dice(unsigned int num); //Random Generator with dice model
    unsigned long generateUniqueID(); //Create unique ID for Seed
    void randomWalk(agent *ag);
    void run(agent *ag);
    void chase(agent *ag);
    float moveLimitter(float aposi);
//    sl_scaled_position randomizePosition();
//    sl_scaled_position move(interaction_mode mode, float mov, sl_scaled_position here, sl_scaled_position target);
    
private:
    unsigned int id_counter;
    unsigned long pre_id;

};

#endif
