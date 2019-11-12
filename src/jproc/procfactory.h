
#ifndef PROCFACTORY_H
#define PROCFACTORY_H

#include <iostream>

#include "basicproc.h"
#include "gridproc.h"
#include "wallproc.h"

enum TYPE_PROCESS: int {
    GRID = 0,
    WALL = 1
};

class FactoryProcess {
public:
    static BasicProc * getProcess(int type_process);
    
};

#endif

