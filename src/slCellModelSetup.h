//
//  slCellModelSetup.h
//  clTestCase
//
//  Created by sonir on 10/27/14.
//
//

#ifndef clTestCase_slCellModelSetup_h
#define clTestCase_slCellModelSetup_h


//Debug
//#define MONITOR_AGENTS

//System
#define NOT_FOUND -1

//For Agent Motion
#define BASIC_MOV_FIX 0.2f//0.2f
#define BASIC_RANDOM_WALK_FIX 0.1f//0.1f
#define ATTACK_LENGTH 0.15f

//For Agent Data 
#define AG_MAX_NUM 4


//enum for interaction mode
typedef enum interaction_mode {RANDOM_WALK, CHASE, RUN, ATTACK, DMG, DEATH} interaction_mode;

//Phisical Contact Flg

typedef struct phisical_contact_t {
    
    bool ag[AG_MAX_NUM];
    
} phisical_contact_t;


//Agent Structure
typedef struct agent {

    int ag_id;
    float view;
    int strength; //This is percentage. Thw max is 100%
    int dexterity; //This is percentage. The max is 100%.
    float hp;
    int inertia;
    float circumference_posi;
    sl_scaled_position posi;
    int contact_flg; // -1 means "not contacted".
    interaction_mode action_flg;
    
} agent;



#endif
