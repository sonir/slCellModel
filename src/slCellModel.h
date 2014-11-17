
#ifndef slCellModel_h
#define slCellModel_h

#include <iostream>
#include "cellModelDataFoundation.h"
#include "slCellModelSetup.h"
#include "Toolkit.h"

class slCellModel : public cellModelDataFoundation {

	public:
        slCellModel(); //Constructor
        slCellModel(double screen_w, double screen_h); //Constructor2
        slEuclid *euclid;
        void syncTouchEvent(phisical_contact_t got_touched);
        void initTouchEvent();
        void initTouchEvent(int this_ag);
        void interactWith(int i , int nearest_id);
        void stroke(int ag_id);
        void cycle();
        float mov_fix;
        float random_walk_fix;
        void setMovFix(float fval);
        void setRandomWalkFix(float fval);
        ToolKit toolKit;
        phisical_contact_t touched;

    
    private:
        int contactCheck(int target);
        bool attackCheck(agent *target, agent *another);
        interaction_mode action(agent *ag);


};



#endif

