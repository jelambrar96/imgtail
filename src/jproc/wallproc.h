#ifndef WALLPROC_H
#define WALLPROC_H

#include "basicproc.h"

#include <vector>
#include <opencv2/core/core.hpp>

class WallProc : public BasicProc {

public:

    WallProc();
    ~WallProc();
    
    void generateTails();

};

#endif

