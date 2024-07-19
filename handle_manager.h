#include <iostream>
#include <memory>
#include <vector>
#include "qcarcam.h"

#ifndef __HANDLE_MANAGER_H
#define __HANDLE_MANAGER_H
class HandleManager {
public:
    static HandleManager& getInstance() {
        static HandleManager HandleManager;
        return HandleManager;
    }

    QCarCamRet_e pushHandle(QCarCamHndl_t* hndl);

    QCarCamRet_e setHandleBuffer(int32_t hndlNum, QCarCamBufferList_t bufferList);

    QCarCamRet_e findHandleBuffer(int32_t hndlNum, QCarCamBufferList_t* bufferList);

    QCarCamRet_e findHandle(const int32_t hndlNum, QCarCamHndl_t* pHndl);
    
    HandleManager(const HandleManager&) = delete;
    HandleManager& operator=(const HandleManager&) = delete;

private:
    HandleManager() {
        std::cout << "HandleManager Constructor Called" << std::endl;
    };

    int32_t handleNum = 1;

    std::vector<QCarCamHndl_t*> vHandleList;
};
#endif