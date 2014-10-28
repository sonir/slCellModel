//
//  toolkit.cpp
//  gismo
//
//  Created by isana137 on 12/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "toolkit.h"
#include<stdlib.h>
#include <time.h> //For random


ToolKit::ToolKit()
{
    printf("toolkit constructor invoked\n");

    //Creating Random Number with the range of num
    srand((unsigned)time(NULL)); //Set seed to rand
    id_counter = 0; //init id counter for generate unique id
    pre_id = 0;
    
}

int ToolKit::dice(unsigned int num)
{    
    //If you want srand each time, use the bellow code.
    //srand((unsigned)clock()); //Set seed to rand

    int random_num = (rand() % num) + 1; //get num from 0 to 99
    return random_num;     
    
}


//Generating of uniqueID for seed

unsigned long ToolKit::generateUniqueID()
{
    
    //srand((unsigned)clock()); //Set seed to rand

    unsigned long generated_id; //For Storage created ID
    
    //Creating number with timer from the point of application launch
    unsigned long tick = (unsigned long)clock();
    
    //Creating number from 1970/1/1
    time_t now;
    time(&now);
    
    //Creating Random Number from 0-99
    int random_num = ( rand() % 100 ) + 1; //get num from 0 to 99
    
    //Make big variation
    int i = ( rand() % 3 );
    float fnum;
    switch(i){
        case 0:
            fnum = 1.;
            break;
        case 1:
            fnum = 0.5;
            break;
        case 2:
            fnum = 2.;
            break;
        default:
            fnum = 137.;
            break;
    }
        
    //Storage the created random numbers
    //generated_id = (((unsigned long)tick + ((unsigned long)now * (((rand() % 10 ) + 1))*id_counter) + (unsigned long)random_num) * fnum)+id_counter;    
    generated_id = (((unsigned long)now + ((unsigned long)tick * (((rand() % 10 ) + 1))*id_counter) + (unsigned long)random_num) * fnum)+id_counter;
    //Increment the id_counter
    id_counter++;
    
    generated_id=generated_id+(generated_id-pre_id);
    
    pre_id=generated_id;
    
    //Return it
    return generated_id;

}


void ToolKit::randomWalk(agent *ag){
    
    float direction = (float)1-( (dice(2)-1)*2 );
    float next = ( (float)dice(100)*0.01f*direction ) * RANDOM_WALK_FIX;
    ag->inertia = direction; //Update the move direction.
    ag->circumference_posi+=next;
    ag->circumference_posi=moveLimitter(ag->circumference_posi);

    
}

void ToolKit::run(agent *ag){

    //Invert the move direction
    ag->inertia *= -1;
    float next = ( (((float)dice(100)*0.01f)*ag->inertia) * MOV_FIX ); //Move Positive
    ag->circumference_posi+=next;
    ag->circumference_posi=moveLimitter(ag->circumference_posi);
    
    
}

void ToolKit::chase(agent *ag){
    float next = ( (((float)dice(100)*0.01f)*ag->inertia) * MOV_FIX ); //Move Positive
    ag->circumference_posi=moveLimitter(ag->circumference_posi);
    
}


float ToolKit::moveLimitter(float aposi){
    
    //If the position exceeds the area, set to the max or min value.
    if (aposi>1.0f)return 1.0f;
    else if (aposi < -1.0f)return -1.0f;
    else return aposi;
    
}

float ToolKit::hpLimitter(float hp){
    
    //If the position exceeds the area, set to the max or min value.
    if (hp>1.0f) return 1.0f;
    else if (hp < -1.0f) return -1.0f;
    else return hp;
    
}


////sl_scaled_position Randomizer
//sl_scaled_position ToolKit::randomizePosition()
//{
//    sl_scaled_position posi;
//    posi.x = (float)dice(20);
//    posi.y = (float)dice(20);
//    
//    posi.x = ((posi.x-10.)/10.);
//    posi.y = ((posi.y-10.)/10.);
//    
//    return posi;
//    
//}
//
//
////Moving Function for Agent
//sl_scaled_position  ToolKit::move(interaction_mode mode, float mov, sl_scaled_position here, sl_scaled_position target)
//{
//    
//    sl_scaled_position next_posi;
//
//    //Create the random number for moving
//    float mov_dist_1 = ((float)dice(1200)*mov)*0.001;
//    float mov_dist_2 = ((float)dice(1200)*mov)*0.001;    
//
//    switch(mode)
//    {
//        case CHASE:
//            //Chase X Axis
//            if(here.x < target.x)next_posi.x = here.x + (mov_dist_1*MOV_FIX);
//            else next_posi.x = here.x - (mov_dist_1*MOV_FIX);
//            //Chase Y Axis
//            if(here.y < target.y)next_posi.y = here.y + (mov_dist_2*MOV_FIX);
//            else next_posi.y = here.y - (mov_dist_1*MOV_FIX);
//            break;
//
//        case RUN:
//            //Chase X Axis
//            if(here.x < target.x)next_posi.x = here.x - (mov_dist_1*MOV_FIX);
//            else next_posi.x = here.x + (mov_dist_1*MOV_FIX);
//            //Chase Y Axis
//            if(here.y < target.y)next_posi.y = here.y - (mov_dist_2*MOV_FIX);
//            else next_posi.y = here.y + (mov_dist_1*MOV_FIX);
//            break;
//            
//        case RANDOM_WALK:
//            //Random Walk for X Axis
//            if(dice(2)==2)next_posi.x = here.x + (mov_dist_1*RANDOM_WALK_FIX);
//            else next_posi.x = here.x - (mov_dist_1*RANDOM_WALK_FIX);
//            //Random Walk for Y Axis
//            if(dice(2)==2)next_posi.y = here.y + (mov_dist_2*RANDOM_WALK_FIX);
//            else next_posi.y = here.y - (mov_dist_2*RANDOM_WALK_FIX);            
//            break;
//            
//        default:
//            printf("ERROR: in ToolKit.move - the others of CHASE, RUN, RANDOM_WALK are utilized to move\n ");
//            break;
//            
//            
//    }
//    
//
//    //Loop of World
//    //For X
//    if(next_posi.x > 1.) next_posi.x = (-1. + (next_posi.x - 1.)); // Move the agent to other size with exceeding distance
//    else if (next_posi.x < -1.) next_posi.x = ( 1. + (next_posi.x+1.)); // Invert process
//    //For Y
//    if(next_posi.y > 1.) next_posi.y = (-1. + (next_posi.y - 1.)); // Same as above
//    else if (next_posi.y < -1.) next_posi.y = ( 1. + (next_posi.y+1.)); // Same as above
//            
//                                               
//    return next_posi;
//
//     //return here;
//    
//}
