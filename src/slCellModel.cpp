
#include "slCellModel.h"
using namespace std;


slCellModel::slCellModel(){
    
    //Instantiate euclid space handller.
    euclid = new slEuclid;
    
}


int slCellModel::contactCheck(int target){
    
    //Copy all agents positions into an array
    sl_eudlid_position agents_positions[AG_MAX_NUM];
    for(int i = 0; i<AG_MAX_NUM; i++) agents_positions[i]=agents[i].posi;
    int nearest_ag = euclid->whoisNearest(agents[target].posi, agents_positions, AG_MAX_NUM, target);
    
    float dist = euclid->distance(agents[target].posi, agents[nearest_ag].posi);
    
    //If the nearest other is less than view
    if(dist <= agents[target].view) return nearest_ag; //Return id of the nearest agent
    else return NOT_FOUND; //It is out of range, return the flag.
    
}

bool slCellModel::attackCheck(agent *target, agent *another){
    
    
    //Attack roll
    if(toolKit.dice(100)<= target->strength){
        
        //Defence Roll
        if(toolKit.dice(100)>= another->dexterity) return true; //If the other misses defence, the attack is success.
        
    }
    
    return false;
    
}

void slCellModel::interactWith(int i, int nearest_id){

    //Set Action into RANDOM_WALK or RUN or CHASE flag through some rolls
    
    //If the agent damaged, do not anything, just do damaged action
    if(agents[i].action_flg==DMG) return;
    
    //The other was Not found, then random walk
    if(nearest_id == NOT_FOUND) {
        
        agents[i].action_flg = RANDOM_WALK;
        return;
        
    }
    
    //Set address of the pair of agents
    agent *target = &agents[i];
    agent *another = &agents[nearest_id];
    
    //Attack Process
    if(this->attackCheck(target, another)){
        //If the attack was successed do as follows,
        target->action_flg = CHASE; //Set flag into chase
        if(euclid->distance(target->posi, another->posi) <= ATTACK_LENGTH){ // If their come close, do attack

            target->action_flg = ATTACK;
//            another->hp -= (float)toolKit.dice(10)*0.01f; //Decreasing the hp
//            target->action_flg = ATTACK; //Set the flg
//            another->action_flg = DMG;
        }
    } else target->action_flg = RUN;
    
    
}

interaction_mode slCellModel::action(agent *ag){
 
    agent *another = &agents[ag->contact_flg];
    
    
    switch (ag->action_flg){
            
        case RANDOM_WALK:
            cout << "random" << endl;
            toolKit.randomWalk(ag);
            return RANDOM_WALK;
            break;
            
        case RUN:
            cout << "run" << endl;
            toolKit.run(ag);
            return RUN;
            break;
            
        case CHASE:
            cout << "chase" << endl;
            toolKit.chase(ag);
            return CHASE;
            break;
            
        case ATTACK:
            cout << "Attack" << endl;
            another->hp -= (float)toolKit.dice(10)*0.01f; //Decreasing the hp
            another->action_flg = DMG;
            return ATTACK;
            break;

        case DMG:
            cout << "dmg" << endl;
            ag->action_flg = RANDOM_WALK; //When Damaged round do not move
            return DMG;
            break;
            
        case DEATH:
            return DEATH;
            break;
            
        default:
            return RANDOM_WALK;
            break;
            
    }
    
    
}


void slCellModel::cycle(){
    
    //Make agent interact with each others
    for (int i = 0; i < AG_MAX_NUM; i++){
        
        //Check contact with others of not (contact_flg will have the neares id)
        agents[i].contact_flg = contactCheck(i);
        
        //Make interact with the nearest agent
        interactWith(i, agents[i].contact_flg);

        //Do the set Action
        this->action(&agents[i]);
        
//        //If the agent attacked, apply damage routine to the another.
//        if (agents[i].action_flg==ATTACK){
//            agents[agents[i].contact_flg].action_flg == DMG; //Set the flag to DMG
//            this->action(&agents[agents[i].contact_flg]); //Do DMG Routine
//        }
        
#ifdef MONITOR_AGENTS
        cout << "agent-" << i << " : hp:" << agents[i].hp << " arc position:" << agents[i].arc_position << " posi x:" << agents[i].posi.x << " posi y:" << agents[i].posi.y << endl;
#endif
        
    }
    
    
}