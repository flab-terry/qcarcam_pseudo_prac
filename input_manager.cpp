#include "input_manager.h"

QCarCamRet_e InputManager::getInput(QCarCamInput_t* pInput, uint32_t inputId) {
    if(pInput == NULL) {
        return QCARCAM_RET_BADPARAM;
    } else {
        switch(inputId) {
            case 0: 
            *pInput = rvcInput;
            return QCARCAM_RET_OK;

            case 1:
            *pInput = cmsLeftInput;
            return QCARCAM_RET_OK;

            case 2:
            *pInput = cmsRightInput;
            return QCARCAM_RET_OK;

            default:
            return QCARCAM_RET_FAILED;
        } 
    }
}

QCarCamRet_e InputManager::getModes(uint32_t id, QCarCamInputModes_t* pInputModes) {
    if(pInputModes == NULL) return QCARCAM_RET_BADPARAM;
    switch(id) {
        case 0: 
        *pInputModes = rvcModes;
        return QCARCAM_RET_OK;

        case 1:
        *pInputModes = leftModes;
        return QCARCAM_RET_OK;

        case 2:
        *pInputModes = rightModes;
        return QCARCAM_RET_OK;

        default:
        return QCARCAM_RET_FAILED;
    } 
} 