#include <iostream>
#include <cstdint>
#include <mutex>
#include "qcarcam.h"

#ifndef __BUFFER_T_
#define __BUFFER_T_
struct Buffer_t{
    uint32_t bufferId;
    uint32_t bufferIndex;
    QCarCamBuffer_t* pBuffers;

    void description() {
        std::cout << ", bufferId : " << bufferId << ", bufferIndex : " << bufferIndex << ", pBuffers : " << pBuffers << std::endl; 
    };
};

#endif