#include <iostream>
#include "qcarcam.h"

#ifndef __CAMERA_H
#define __CAMERA_H
class Camera {
public:
    QCarCamInit_t qcarcam_init;

    QCarCamRet_e setApiVersion(uint32_t version);

    QCarCamRet_e setInput(QCarCamInput_t input, uint32_t* id);

    QCarCamRet_e setQueryInputModes(QCarCamInputModes_t inputModes);

    QCarCamRet_e setOpenParam(QCarCamOpen_t& rOpenParam);

    QCarCamRet_e setOpenHandle(QCarCamHndl_t& rOpenHandle);

    QCarCamRet_e getCameraInit(QCarCamInit_t& rCameraInit);

    QCarCamRet_e getCameraId(uint32_t& pId);

    QCarCamRet_e getHandle(QCarCamHndl_t* inputHndl);

    void test_handle();

    Camera();

private:
    QCarCamInit_t cameraInit;
    QCarCamInput_t cameraInput;
    QCarCamInputModes_t queryInputModes;
    uint32_t cameraId;
    QCarCamOpen_t cameraOpen;
    QCarCamHndl_t cameraHndl = QCARCAM_HNDL_INVALID;
    QCarCamOpen_t openParams;
};
#endif