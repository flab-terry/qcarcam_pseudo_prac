#include "handle_manager.h"

QCarCamRet_e HandleManager::pushHandle(QCarCamHndl_t* hndl) {
    try{
        hndl->hndlNum = vHandleList.size();
        vHandleList.push_back(hndl);
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e HandleManager::setHandleBuffer(int32_t hndlNum, QCarCamBufferList_t bufferList) {
    try {
        vHandleList[hndlNum]->pBufferList = bufferList;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e HandleManager::findHandleBuffer(int32_t hndlNum, QCarCamBufferList_t* bufferList) {
    if(bufferList == NULL) return QCARCAM_RET_BADPARAM;
    try {
        *bufferList = vHandleList[hndlNum]->pBufferList;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e HandleManager::findHandle(const int32_t hndlNum, QCarCamHndl_t* pHndl) {
    try {
        if(vHandleList[hndlNum] != NULL) {
            *pHndl = *vHandleList[hndlNum];
            return QCARCAM_RET_OK;
        }
        return QCARCAM_RET_FAILED;
    } catch(...) {
        return QCARCAM_RET_OK;
    }
}