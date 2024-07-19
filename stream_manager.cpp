#include "stream_manager.h"

QCarCamRet_e StreamManager::createQueue(int32_t hndl, const QCarCamBufferList_t pBuffers) {
    try{
        std::queue<Buffer_t> qTempQueue;
        for(uint32_t i = 0; i < pBuffers.nBuffers; ++i) {
            Buffer_t buffer {
                .bufferId = pBuffers.id,
                .bufferIndex = i,
                .pBuffers = &pBuffers.pBuffers[i]
            };
            qTempQueue.push(buffer);
        }
        mQueueList[hndl] = qTempQueue;
        std::shared_ptr<std::mutex> pMutex = std::make_shared<std::mutex>();
        mMutexList[hndl] = pMutex;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::requestStream(QCarCamHndl_t hndl) {
    try{
        num = 10;
        std::thread record = std::thread(&StreamManager::startStream, this, hndl);
        mThreadList[hndl.hndlNum] = record.native_handle();
        record.detach(); 
        return QCARCAM_RET_OK;   
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::getStreamBuffer(int32_t hndlNum, Buffer_t* frameBuffer, const uint64_t timeout) {
    if(mQueueList[hndlNum].empty()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
        if(mQueueList[hndlNum].empty()) return QCARCAM_RET_TIMEOUT;
    }
    try{
        pop(hndlNum, frameBuffer);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::releaseStreamBuffer(int32_t hndlNum, uint32_t id, uint32_t bufferIndex, QCarCamBuffer_t* buffer) {
    try{
        Buffer_t frameBuffer;
        frameBuffer.bufferId = id;
        frameBuffer.bufferIndex = bufferIndex;
        frameBuffer.pBuffers = buffer;
        push(hndlNum, frameBuffer);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::stopStream(int32_t hndlNum) {
    try{
        if(mThreadList.empty() || mThreadList.count(hndlNum) == 0) return QCARCAM_RET_BADSTATE;
        pthread_cancel(mThreadList[hndlNum]);
        mThreadList.erase(hndlNum);
        mQueueList.erase(hndlNum);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::pauseStream(int32_t hndlNum)
{   
    try{
        if(mThreadList.empty() || mThreadList.count(hndlNum) == 0) return QCARCAM_RET_BADSTATE;
        pthread_cancel(mThreadList[hndlNum]);
        mThreadList.erase(hndlNum);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::resumeStream(QCarCamHndl_t hndl)
{
    if(mQueueList.count(hndl.hndlNum) == 0) return QCARCAM_RET_BADSTATE;
    try{
        std::thread record = std::thread(&StreamManager::startStream, this, hndl);
        mThreadList[hndl.hndlNum] = record.native_handle();
        record.detach(); 
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
     
}

QCarCamRet_e StreamManager::startStream(QCarCamHndl_t hndl) {
    int32_t hndlNum = hndl.hndlNum;
    //std::shared_ptr<std::mutex> pMutex = mMutexList[hndlNum];
    Buffer_t streamBuffer;
    while(1) {
        if(!mQueueList[hndlNum].empty()) {
            pop(hndlNum, &streamBuffer);
            for(uint32_t i = 0; i < streamBuffer.pBuffers->numPlanes; ++i) {
                int* memHndl = reinterpret_cast<int*>(streamBuffer.pBuffers->planes[i].memHndl);
                *memHndl = num;
                ++num;
            }
            push(hndlNum, streamBuffer);
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    return QCARCAM_RET_TIMEOUT;
}

QCarCamRet_e StreamManager::pop(int32_t hndlNum, Buffer_t* buffer) {
    try {
        mMutexList[hndlNum]->lock();
        *buffer = mQueueList[hndlNum].front();
        mQueueList[hndlNum].pop();
        mMutexList[hndlNum]->unlock();
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e StreamManager::push(int32_t hndlNum, Buffer_t& buffer) {
    try {
        //Buffer_t buffer = buffer;
        mMutexList[hndlNum]->lock();
        mQueueList[hndlNum].push(buffer);
        mMutexList[hndlNum]->unlock();
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}