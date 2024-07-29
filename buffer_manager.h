#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <functional>
#include <mutex>
#include <queue>
#include <unistd.h>
#include <map>
#include <string>
#include <sstream>
#include "qcarcam.h"
#include "buffer.h"

#ifndef __BUFFER_MANAGER_
#define __BUFFER_MANAGER_
class BufferManager {
public:
    static BufferManager& getInstance() {
        static BufferManager bufferManager;
        return bufferManager;
    }

    QCarCamRet_e createTestBuffer(const uint32_t bufferSize, std::shared_ptr<QCarCamBufferList_t>* bufferList);

    QCarCamRet_e createVideoBuffer(const uint32_t bufferSize, std::shared_ptr<QCarCamBufferList_t>* bufferList);

    QCarCamRet_e findBufferList(const uint32_t bufferListId, QCarCamBufferList_t* bufferList);

    QCarCamRet_e getMemHndl(const uint32_t bufferListId, uint32_t bufferIndex, uint32_t plnaeIndex, uint64_t* memHndl);

    std::string getDescription(QCarCamFrameInfo_t frameInfo, uint32_t planeIndex);

private:
    BufferManager() {
        std::cout << "BufferManager Constructor Called" << std::endl;
    };

    QCarCamRet_e createMemHndl(uint64_t* memHndl);

    QCarCamRet_e createVideoMemHndl(uint64_t* memHndl);

    int num = 10;

    std::vector<std::shared_ptr<int>> vMemHndl;
    std::vector<std::shared_ptr<QCarCamBufferList_t>> vBufferList;
    std::vector<std::shared_ptr<QCarCamBuffer_t[]>> vBuffers;
    QCarCamRet_e ret;
};
#endif