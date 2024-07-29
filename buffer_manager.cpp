#include "buffer_manager.h"

QCarCamRet_e BufferManager::createTestBuffer(const uint32_t bufferSize, std::shared_ptr<QCarCamBufferList_t>* bufferList) {
    if(bufferList == NULL) return QCARCAM_RET_BADPARAM;
    try {
        std::shared_ptr<QCarCamBufferList_t> pBufferList = std::make_shared<QCarCamBufferList_t>();
        std::shared_ptr<QCarCamBuffer_t[]> pBuffer(new QCarCamBuffer_t[bufferSize]);

        for(uint32_t i = 0; i<bufferSize; i++) {
            ret = createMemHndl(&pBuffer[i].planes[0].memHndl); // example address to buffer handle
            if(ret != QCARCAM_RET_OK) {
                std::cout << "error has occured when create buffer[" << i << "]" << std::endl;
            }
            pBuffer[i].numPlanes = 1;
            pBuffer[i].planes[0].width = 1920;
            pBuffer[i].planes[0].height = 1080;
            pBuffer[i].planes[0].stride = 1920 * 2;
            pBuffer[i].planes[0].size = 1920 * 1080 * 2;

            
        }
        vBuffers.push_back(pBuffer);
        
        pBufferList->id = (uint32_t)vBufferList.size();
        pBufferList->colorFmt = QCARCAM_FMT_UYVY_8;
        pBufferList->pBuffers = pBuffer.get();
        pBufferList->nBuffers = bufferSize;

        vBufferList.push_back(pBufferList);
        *bufferList = pBufferList;

        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e BufferManager::createVideoBuffer(const uint32_t bufferSize, std::shared_ptr<QCarCamBufferList_t>* bufferList) {
    if(bufferList == NULL) return QCARCAM_RET_BADPARAM;
    try {
        std::shared_ptr<QCarCamBufferList_t> pBufferList = std::make_shared<QCarCamBufferList_t>();
        std::shared_ptr<QCarCamBuffer_t[]> pBuffer(new QCarCamBuffer_t[bufferSize]);

        for(uint32_t i = 0; i<bufferSize; i++) {
            ret = createMemHndl(&pBuffer[i].planes[0].memHndl); // example address to buffer handle
            if(ret != QCARCAM_RET_OK) {
                std::cout << "error has occured when create buffer[" << i << "]" << std::endl;
            }
            pBuffer[i].numPlanes = 1;
            pBuffer[i].planes[0].width = 1920;
            pBuffer[i].planes[0].height = 1080;
            pBuffer[i].planes[0].stride = 1920 * 2;
            pBuffer[i].planes[0].size = 1920 * 1080 * 2;

            
        }
        vBuffers.push_back(pBuffer);
        
        pBufferList->id = (uint32_t)vBufferList.size();
        pBufferList->colorFmt = QCARCAM_FMT_UYVY_8;
        pBufferList->pBuffers = pBuffer.get();
        pBufferList->nBuffers = bufferSize;

        vBufferList.push_back(pBufferList);
        *bufferList = pBufferList;

        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e BufferManager::findBufferList(const uint32_t bufferListId, QCarCamBufferList_t* bufferList) {
    for(std::vector<std::shared_ptr<QCarCamBufferList_t>>::iterator it = vBufferList.begin(); it != vBufferList.end(); ++it) {
        if(it->get()->id == bufferListId) {
            *bufferList = *it->get();
            return QCARCAM_RET_OK;
        }
    }
    return QCARCAM_RET_FAILED;
}

QCarCamRet_e BufferManager::getMemHndl(const uint32_t bufferListId, uint32_t bufferIndex, uint32_t planeIndex, uint64_t* memHndl)
{
    QCarCamBufferList_t bufferList;
    ret = findBufferList(bufferListId, &bufferList);
    if(ret != QCARCAM_RET_OK) return ret;
    *memHndl = bufferList.pBuffers[bufferIndex].planes[planeIndex].memHndl;
    return ret;
}

std::string BufferManager::getDescription(QCarCamFrameInfo_t frameInfo, uint32_t planeIndex)
{
    uint64_t memHndl;
    getMemHndl(frameInfo.id, frameInfo.bufferIndex, planeIndex, &memHndl);
    std::ostringstream ss;
    ss << reinterpret_cast<int*>(memHndl);
    std::string description = std::to_string(frameInfo.id) + " : pBuffer[" + std::to_string(frameInfo.bufferIndex) + "] : " + ss.str() + " : " + std::to_string(*reinterpret_cast<int*>(memHndl));
    return description;
}

QCarCamRet_e BufferManager::createMemHndl(uint64_t* memHndl) {
    if(memHndl == NULL) return QCARCAM_RET_BADPARAM;
    try {
        std::shared_ptr<int> pMemHndl = std::make_shared<int>(1);
        *memHndl = reinterpret_cast<uint64_t>(pMemHndl.get());
        //std::cout << "BufferManager : createBuffer : memHndl = " << reinterpret_cast<uint64_t>(pInt) << std::endl;

        vMemHndl.push_back(pMemHndl);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e BufferManager::createVideoMemHndl(uint64_t* memHndl) {
    if(memHndl == NULL) return QCARCAM_RET_BADPARAM;
    try {
        std::shared_ptr<int> pMemHndl = std::make_shared<int>(num);
        ++num;
        *memHndl = reinterpret_cast<uint64_t>(pMemHndl.get());
        //std::cout << "BufferManager : createBuffer : memHndl = " << reinterpret_cast<uint64_t>(pInt) << std::endl;

        vMemHndl.push_back(pMemHndl);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}