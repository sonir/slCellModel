//
//  cellModelDataFoundation.h
//  clTestCase
//
//  Created by sonir on 10/27/14.
//
//

#ifndef __clTestCase__cellModelDataFoundation__
#define __clTestCase__cellModelDataFoundation__

#include <stdio.h>
#include <iostream>
#include "slEuclid.h"
#include "Toolkit.h"


class cellModelDataFoundation {
    
    
    public:
        cellModelDataFoundation(); //Constructor
        int addAgent(agent *ag);
        agent getAgent(int at_index);
    
        agent agents[AG_MAX_NUM];
        int agent_count;

    
    
};

#endif /* defined(__clTestCase__cellModelDataFoundation__) */
