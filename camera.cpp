#include "camera.h"

Camera::Camera() {
    cameraInit = {};
    cameraInit.apiVersion = 10;
}

QCarCamRet_e Camera::setApiVersion(uint32_t version) {
    try{
        cameraInit.apiVersion = version;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e Camera::setInput(QCarCamInput_t input, uint32_t* id) {
    try{
        cameraInput = input;
        *id = input.inputId;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
    
}

QCarCamRet_e Camera::setQueryInputModes(QCarCamInputModes_t inputModes) {
    try{
        queryInputModes = inputModes;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e Camera::setOpenParam(QCarCamOpen_t& rOpenParam) {
    try {
        openParams = rOpenParam;
        return QCARCAM_RET_OK;
    } catch(...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e Camera::setOpenHandle(QCarCamHndl_t& rOpenHandle) {
    try {
        cameraHndl = rOpenHandle;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
};

QCarCamRet_e Camera::getCameraInit(QCarCamInit_t& rCameraInit) {
    try{
        rCameraInit = cameraInit;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e Camera::getCameraId(uint32_t& pId) {
    try {
        pId = cameraId;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
}

QCarCamRet_e Camera::getHandle(QCarCamHndl_t* inputHndl) {
    if(inputHndl == NULL) return QCARCAM_RET_BADPARAM;

    try{
        *inputHndl = cameraHndl;
        return QCARCAM_RET_OK;
    } catch (...) {
        return QCARCAM_RET_FAILED;
    }
}

void Camera::test_handle() {
    std::cout << "Handle address : " << &cameraHndl << ", handle number = " << cameraHndl.hndlNum << std::endl;
}
