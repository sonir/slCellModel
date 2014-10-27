
#ifndef slCellModel_h
#define slCellModel_h

#include <iostream>
#include "cellModelDataFoundation.h"

class slCellModel : public cellModelDataFoundation {

	public:
        slCellModel(); //Constructor
		void test();
        slEuclid *euclid;

};



#endif

