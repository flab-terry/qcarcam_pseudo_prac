#include <iostream>
#include "qcarcam.h"

#ifndef __TEST_INPUT_H
#define __TEST_INPUT_H
class InputManager {
public:
    static InputManager& getInstance() {
        static InputManager instance;
        return instance;
    }

    QCarCamRet_e getInput(QCarCamInput_t* pInput, uint32_t inputId);

    QCarCamRet_e getModes(uint32_t id, QCarCamInputModes_t* pInputModes);

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

private:
    InputManager() {
        std::cout << "InputManager Constructor Called" << std::endl;
    };

    const QCarCamInputSrc_t rvcCamera = {0, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 0};
    const QCarCamInputSrc_t topOfLeftCamera = {1, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 0};
    const QCarCamInputSrc_t bottomOfLeftCamera = {2, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 0};
    const QCarCamInputSrc_t topOfRightCamera = {3, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 0};
    const QCarCamInputSrc_t bottomOfRightCamera = {4, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 0};

    QCarCamMode_t rearViewMode0 = {{rvcCamera}, 1};
    QCarCamMode_t rearViewModes[1] = {rearViewMode0};

    QCarCamMode_t leftViewMode0 = {{topOfLeftCamera}, 1};
    QCarCamMode_t leftViewMode1 = {{bottomOfLeftCamera}, 1};
    QCarCamMode_t leftViewMode2 = {{topOfLeftCamera, bottomOfLeftCamera}, 2};
    QCarCamMode_t leftViewModes[3] = {leftViewMode0, leftViewMode1, leftViewMode2};

    QCarCamMode_t rightViewMode0 = {{topOfRightCamera}, 1};
    QCarCamMode_t rightViewMode1 = {{bottomOfRightCamera}, 1};
    QCarCamMode_t rightViewMode2 = {{topOfRightCamera, bottomOfRightCamera}, 2};
    QCarCamMode_t rightViewModes[3] = {rightViewMode0, rightViewMode1, rightViewMode2};

    QCarCamInputModes_t rvcModes = {0, 1, rearViewModes};
    QCarCamInputModes_t leftModes = {0, 3, leftViewModes};
    QCarCamInputModes_t rightModes = {0, 3, rightViewModes};

    QCarCamInput_t rvcInput = {0, 0, 0, "Rear_View", 1, 0};
    QCarCamInput_t cmsLeftInput = {1, 1, 0, "Left_View", 3, 0};
    QCarCamInput_t cmsRightInput = {2, 1, 1, "Right_View", 3, 0};
};
#endif