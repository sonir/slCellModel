
#include "slCellModel.h"
using namespace std;


slCellModel::slCellModel(){
    
    //Instantiate euclid space handller.
    euclid = new slEuclid;
    
    setMovFix(BASIC_MOV_FIX);
    setRandomWalkFix(BASIC_RANDOM_WALK_FIX);
    
    //Init Touched Event Memory
    for(int i =0; i<AG_MAX_NUM; i++)
    {
        touched.ag[i] = false;
    }
    
    
}

slCellModel::slCellModel(double screen_w, double screen_h){
    
    //Instantiate euclid space handller.
    euclid = new slEuclid(screen_w, screen_h);
    
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

void slCellModel::syncTouchEvent(phisical_contact_t got_touched){
    

    for(int i=0; i< AG_MAX_NUM; i++){
        
        //Log the result until init
        touched.ag[i] = touched.ag[i] || got_touched.ag[i];        

    }
    
    
}

void slCellModel::initTouchEvent(){
    
//    touched.ag[AG_MAX_NUM] = { 0 };
    for (int i=0; i<AG_MAX_NUM; i++){
        
        touched.ag[i] = false;
        
    }
    
}

void slCellModel::initTouchEvent(int this_ag){ // For set each
    
    
        touched.ag[this_ag] = false;
    
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
        //If the agent comes close, then attack
        if(euclid->distance(target->posi, another->posi) <= ATTACK_LENGTH) target->action_flg = ATTACK;
    
    }else target->action_flg = RUN;
    
    
}

interaction_mode slCellModel::action(agent *ag){
 
    agent *another = &agents[ag->contact_flg];
    
    
    float dmg_val = 0.0f;
    switch (ag->action_flg){
            
        case RANDOM_WALK:
//            cout << "random" << endl;
            toolKit.randomWalk(ag);
            return RANDOM_WALK;
            break;
            
        case RUN:
//            cout << "run" << endl;
            toolKit.run(ag);
            return RUN;
            break;
            
        case CHASE:
//            cout << "chase" << endl;
            toolKit.chase(ag);
            return CHASE;
            break;
            
        case ATTACK:
//            cout << "Attack" << endl;
            dmg_val = (float)(float)toolKit.dice(10)*0.01f;
            another->hp -= dmg_val; //Decreasing the hp
            another->hp = toolKit.hpLimitter(another->hp); //limitter process
            ag->hp += dmg_val;
            ag->hp = toolKit.hpLimitter(ag->hp);
            another->action_flg = DMG;
            return ATTACK;
            break;

        case DMG:
//            cout << "dmg" << endl;
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


void slCellModel::stroke(int ag_id){
    
    //Check contact with others of not (contact_flg will have the neares id)
    agents[ag_id].contact_flg = contactCheck(ag_id);

    // If phisical contact occured, forcely set the nearest agents as contaced.
    if(touched.ag[ag_id]){
        
        //Set the nearest agent as interacted agent
        //TODO:: now ignore touch with human body. please imp it.
        //Copy all agents positions into an array
        sl_eudlid_position agents_positions[AG_MAX_NUM];
        for(int i = 0; i<AG_MAX_NUM; i++) agents_positions[i]=agents[i].posi;
        //Check who is the nearest agent
        int nearest_ag = euclid->whoisNearest(agents[ag_id].posi, agents_positions, AG_MAX_NUM, ag_id);
        //Set the got id as flg
        agents[ag_id].contact_flg=nearest_ag;
        
    }


    

    //Make interact with the nearest agent
    interactWith(ag_id, agents[ag_id].contact_flg);
    
    //Do the set Action
    this->action(&agents[ag_id]);
    
    if(touched.ag[ag_id]){
        //If physical touched, force run
//        agents[ag_id].action_flg=RUN; //OverWrite Flag
//        this->action(&agents[ag_id]);
        toolKit.run(&agents[ag_id]);
//        cout << ag_id << " :touched.RUN" << endl;
    }
    
}

void slCellModel::cycle(){
    
    //Make agent interact with each others
    for (int i = 0; i < AG_MAX_NUM; i++){

        this->stroke(i);        
        
#ifdef MONITOR_AGENTS
        cout << "agent-" << i << " : hp:" << agents[i].hp << " arc position:" << agents[i].arc_position << " posi x:" << agents[i].posi.x << " posi y:" << agents[i].posi.y << endl;
#endif
        
    }
    
    
}

void slCellModel::setMovFix(float fval){
    
    mov_fix = fval;
    toolKit.mov_fix = mov_fix;
    
}

void slCellModel::setRandomWalkFix(float fval){
    
    random_walk_fix = fval;
    toolKit.random_walk_fix = random_walk_fix;
    
}

