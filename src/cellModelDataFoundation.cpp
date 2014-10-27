//
//  cellModelDataFoundation.cpp
//  clTestCase
//
//  Created by sonir on 10/27/14.
//
//

#include "cellModelDataFoundation.h"
using namespace std;

cellModelDataFoundation::cellModelDataFoundation(){

    agent_count = 0;
    
}

int cellModelDataFoundation::addAgent(agent *ag){
    
    //Index Check
    if(agent_count>AG_MAX_NUM) return 1;

    //Set Default Values for system
    ag->id_num = agent_count;
    ag->inertia = 1;
    ag->contact_flg = RANDOM_WALK;
    
    //Copy the data
    agents[agent_count] = *ag;

    //Increment acount
    agent_count++;
    return 0;
    
}


agent cellModelDataFoundation::getAgent(int at_index){
    
    
    return agents[at_index];
    
    
}

void cellModelDataFoundation::setAgent(int at_index, agent *ag){
    
    if(at_index<agent_count){
        agents[at_index] = *ag;
    }
    
}
