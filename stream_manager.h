#include <iostream>
#include <queue>
#include <mutex>
#include <map>
#include <thread>
#include <memory>
#include <pthread.h>
#include "qcarcam.h"
#include "buffer.h"

#ifndef __STREAM_MANAGER_
#define __STREAM_MANAGER_
class StreamManager {
public:
    static StreamManager& getInstance() {
        static StreamManager streamManager;
        return streamManager;
    }

    QCarCamRet_e createQueue(int32_t hndl, const QCarCamBufferList_t pBuffers);

    QCarCamRet_e requestStream(QCarCamHndl_t hndl);

    QCarCamRet_e getStreamBuffer(int32_t hndlNum, Buffer_t* frameBuffer, const uint64_t timeout);

    QCarCamRet_e releaseStreamBuffer(int32_t hndlNum, uint32_t id, uint32_t bufferIndex, QCarCamBuffer_t* buffer);

    QCarCamRet_e stopStream(int32_t hndlNum);

    QCarCamRet_e pauseStream(int32_t hndlNum);

    QCarCamRet_e resumeStream(QCarCamHndl_t hndl);

private:
    StreamManager() {
        std::cout << "Create a new Queue" << std::endl;
    };

    QCarCamRet_e startStream(QCarCamHndl_t hndl);

    QCarCamRet_e pop(int32_t hndlNum, Buffer_t* buffer);

    QCarCamRet_e push(int32_t hndlNum, Buffer_t& buffer);

    std::map<int32_t, std::queue<Buffer_t>> mQueueList;
    std::map<int32_t, std::shared_ptr<std::mutex>> mMutexList;
    std::map<int32_t, pthread_t> mThreadList;

    int32_t num = 1;
    QCarCamRet_e ret;
};
#endif