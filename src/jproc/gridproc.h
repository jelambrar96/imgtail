#ifndef GRIDPROC_H
#define GRIDPROC_H

#include "basicproc.h"

#include <vector>
#include <opencv2/core/core.hpp>

class GridProc : public BasicProc {

public:

    GridProc();
    ~GridProc();
    
    void generateTails();

};

#endif

