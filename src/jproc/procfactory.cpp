#include "procfactory.h"

BasicProc * FactoryProcess::getProcess(int type_process) {

    switch(type_process) {
        case TYPE_PROCESS::GRID:
            return new GridProc();
        case TYPE_PROCESS::WALL:
            return new WallProc();
        default:
            std::cerr << "ERROR: Invalid type:" << std::endl;
            throw;
    }

}
