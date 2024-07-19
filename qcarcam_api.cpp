#include "qcarcam_api.h"

QCarCamRet_e QCarCamInitialize(const QCarCamInit_t* pInitParams) {
    if (pInitParams == nullptr) {
        return QCARCAM_RET_BADPARAM;
    }
    
    if (pInitParams->apiVersion == 10) {
        return QCARCAM_RET_OK;
    } else {
        return QCARCAM_RET_UNSUPPORTED;
    }
}

QCarCamRet_e QCarCamQueryInputs(QCarCamInput_t *pInputs, const uint32_t size, uint32_t *pRetSize) {
    TestInput& testInput = TestInput::getInstance();
    QCarCamRet_e ret;

    if(pRetSize == NULL) {
        return QCARCAM_RET_BADPARAM;
    } else if(pInputs == NULL && size == 0) {
        *pRetSize = 3;
        return QCARCAM_RET_OK;
    } else {
        for(uint32_t i = 0; i <= 2; ++i) {
            ret = testInput.getInput(&pInputs[i], i);

            if (ret != QCARCAM_RET_OK) return ret;
        }
        if(pRetSize != NULL) {
            *pRetSize = 3;
        }
        return QCARCAM_RET_OK;
    }
}

QCarCamRet_e QCarCamQueryInputModes(const uint32_t inputId, QCarCamInputModes_t* pInputModes) {
    try {
        QCarCamRet_e ret = TestInput::getInstance().getModes(inputId, pInputModes);
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
    
}

QCarCamRet_e QCarCamOpen(const QCarCamOpen_t* pOpenParams, QCarCamHndl_t* pHndl) {
    if(pOpenParams == NULL || pHndl == NULL) return QCARCAM_RET_BADPARAM;
    try {
        HandleManager& handleManager = HandleManager::getInstance();
        handleManager.pushHandle(pHndl);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
    
}

QCarCamRet_e QCarCamSetBuffers(const QCarCamHndl_t handle, const QCarCamBufferList_t* pBuffers) {
    if(pBuffers == NULL) return QCARCAM_RET_BADPARAM;
    try{
        HandleManager& handleManager = HandleManager::getInstance();
        QCarCamRet_e ret = handleManager.setHandleBuffer(handle.hndlNum, *pBuffers);
        if(ret != QCARCAM_RET_OK) return QCARCAM_RET_FAILED;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e QCarCamStart(const QCarCamHndl_t hndl) {
    try {
        QCarCamHndl_t rHndl;
        uint32_t bufferListId;
        QCarCamBufferList_t bufferList;

        HandleManager& handleManager = HandleManager::getInstance();
        QCarCamRet_e ret = handleManager.findHandle(hndl.hndlNum, &rHndl);
        if(ret != QCARCAM_RET_OK) return QCARCAM_RET_FAILED;
        ret = handleManager.findHandleBuffer(rHndl.hndlNum, &bufferList);
        //std::cout << "bufferList : "<< bufferList.id << bufferList.nBuffers << bufferList.pBuffers << std::endl;

        StreamManager& streamManager = StreamManager::getInstance();
        ret = streamManager.createQueue(rHndl.hndlNum, bufferList);

        streamManager.requestStream(rHndl);

        return QCARCAM_RET_OK;   
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}


QCarCamRet_e QCarCamGetFrame(const QCarCamHndl_t hndl, QCarCamFrameInfo_t *pFrameInfo, const uint64_t timeout, const uint32_t flags) {
    try {
        QCarCamRet_e ret;
        Buffer_t buffer;
        StreamManager& streamManager = StreamManager::getInstance();
        ret = streamManager.getStreamBuffer(hndl.hndlNum, &buffer, timeout);

        pFrameInfo->id = buffer.bufferId;
        pFrameInfo->bufferIndex = buffer.bufferIndex;
        pFrameInfo->field_type = QCARCAM_INTERLACE_FIELD_UNKNOWN;

        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }  
}

QCarCamRet_e QCarCamReleaseFrame(const QCarCamHndl_t hndl, uint32_t id, uint32_t bufferIndex) {
    QCarCamBufferList_t bufferList;
    HandleManager& handleManager = HandleManager::getInstance();
    StreamManager& streamManager = StreamManager::getInstance();
    
    QCarCamRet_e ret;
    ret = handleManager.findHandleBuffer(hndl.hndlNum, &bufferList);
    ret = streamManager.releaseStreamBuffer(hndl.hndlNum, id, bufferIndex, &bufferList.pBuffers[bufferIndex]);

    return ret;
}

QCarCamRet_e QCarCamStop(const QCarCamHndl_t hndl) {
    StreamManager& streamManager = StreamManager::getInstance();
    QCarCamRet_e ret = streamManager.stopStream(hndl.hndlNum);

    return ret;
}

QCarCamRet_e QCarCamPause(const QCarCamHndl_t hndl)
{
    StreamManager& streamManager = StreamManager::getInstance();
    QCarCamRet_e ret = streamManager.pauseStream(hndl.hndlNum);

    return ret;
}

QCarCamRet_e QCarCamResume(const QCarCamHndl_t hndl)
{
    StreamManager& streamManager = StreamManager::getInstance();
    QCarCamRet_e ret = streamManager.resumeStream(hndl);

    return ret;
}
