#include <iostream>
#include <mutex>
#include "qcarcam.h"

class TestMode {
public:
    static TestMode& getInstance() {
        static TestMode testMode;
        return testMode;
    }

    QCarCamMode_t* getMode(uint32_t index) { return &modeList[index]; }

    TestMode(const TestMode&) = delete;
    TestMode& operator=(const TestMode&) = delete;

private:
    TestMode() {
        std::cout << "TestInput Constructor Called" << std::endl;
    };

    QCarCamMode_t mode_0 {{0, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 10}, 1};
    QCarCamMode_t mode_1 {{1, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 10}, 1};
    QCarCamMode_t mode_2 {{2, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 10}, 1};
    QCarCamMode_t mode_3 {{3, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 10}, 1};
    QCarCamMode_t mode_4 {{4, 1920, 1080, QCARCAM_FMT_RGB_888, 60, 10}, 1};

    QCarCamMode_t modeList[5] = {mode_0, mode_1, mode_2, mode_3, mode_4};
};
