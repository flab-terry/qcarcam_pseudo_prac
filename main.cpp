#include <iostream>
#include <memory>
#include <thread>
#include <opencv4/opencv2/opencv.hpp>
#include "qcarcam.h"
#include "qcarcam_metadata.h"
#include "qcarcam_api.h"
#include "camera.h"
#include "buffer_manager.h"

int main() {
    //------------------create camera instance----------------------------
    Camera sampleVideo;
    QCarCamRet_e ret = sampleVideo.setApiVersion(10);
    if(ret != QCARCAM_RET_OK) {
        std::cout << "setApiVersion fail" << std::endl;
        return -1;
    }

    //-------------------------initialize---------------------------------
    QCarCamInit_t videoInit;
    ret = sampleVideo.getCameraInit(videoInit);
    if(ret != QCARCAM_RET_OK) {
        std::cout << "getCameraInit fail" << std::endl;
        return -1;
    }

    ret = QCarCamInitialize(&videoInit);
    if(ret == QCARCAM_RET_OK) {
        std::cout << "QCarCamInitialize success" << std::endl;
    } else {
        std::cout << "QCarCamInitialize fail" << std::endl;
        return -1;
    }

    //------------------------query inputs---------------------------------
    uint32_t queryNumInputs = 0, queryFilled = 0;
    
    ret = QCarCamQueryInputs(NULL, 0, &queryNumInputs);

    if(ret != QCARCAM_RET_OK) {
        std::cout << "QCarCamInitialize fail" << std::endl;
        return -1;
    }

    QCarCamInput_t pInput[queryNumInputs];

    ret = QCarCamQueryInputs(pInput, queryNumInputs, &queryFilled);
    
    if(ret == QCARCAM_RET_OK) {
        std::cout << "QCarCamQueryInputs success" << std::endl;
    } else {
        std::cout << "QCarCamInitialize fail" << std::endl;
        return -1;
    }

    //-----------------------query input modes------------------------------
    uint32_t videoId;
    ret = sampleVideo.setInput(pInput[3], &videoId);

    if(ret != QCARCAM_RET_OK) {
        std::cout << "get camera ID fail" << std::endl;
        return -1;
    }

    QCarCamInputModes_t queryInputModes = {};

    ret = QCarCamQueryInputModes(videoId, &queryInputModes);
    if(ret != QCARCAM_RET_OK) {
        std::cout << "QCarCamQueryInputMode fail" << std::endl;
        return -1;
    }

    sampleVideo.setQueryInputModes(queryInputModes);
    if(ret == QCARCAM_RET_OK) {
        std::cout << "QCarCamQueryInputMode success" << std::endl;
    } else {
        std::cout << "QCarCamQueryInputMode fail" << std::endl;
        return -1;
    }

    //------------------------qcarcam open----------------------------------
    QCarCamOpen_t openParams = {};

    openParams.opMode = QCARCAM_OPMODE_RAW_DUMP;
    openParams.numInputs = 1;
    openParams.inputs[0].inputId = videoId;
    openParams.inputs[0].srcId = 0;
    openParams.inputs[0].inputMode = 0;

    ret = sampleVideo.setOpenParam(openParams);
    if(ret != QCARCAM_RET_OK) {
        std::cout << "QCarCamOpen fail 1" << std::endl;
        return -1;
    }

    QCarCamHndl_t hndl;

    ret = QCarCamOpen(&openParams, &hndl);
    if(ret != QCARCAM_RET_OK) {
        std::cout << "QCarCamOpen fail 3" << std::endl;
        return -1;
    }
    ret = sampleVideo.setOpenHandle(hndl);
    if(ret == QCARCAM_RET_OK) {
        std::cout << "QCarCamOpen success" << std::endl;
    } else {
        std::cout << "QCarCamOpen fail" << std::endl;
        return -1;
    }

    //---------------------------qcarcam set buffers-------------------------------
    ret = sampleVideo.getHandle(&hndl);

    std::shared_ptr<QCarCamBufferList_t> bufferList{};

    BufferManager& bufferManager = BufferManager::getInstance();
    bufferManager.createTestBuffer(3, &bufferList);
    //QCarCamBuffer_t pBuffer[3];

    ret = QCarCamSetBuffers(hndl, bufferList.get());

    if(ret == QCARCAM_RET_OK) {
        std::cout << "QCarCamSetBuffers success" << std::endl;
    } else {
        std::cout << "QCarCamSetBuffers fail" << std::endl;
        return -1;
    }

    //--------------------------------qcarcam start------------------------------
    ret = QCarCamStart(hndl);

    if(ret != QCARCAM_RET_OK) {
        std::cout << "QCarCamOpen failed" << std::endl;
        return -1;
    } else {
        std::cout << "QCarCamOpen success" << std::endl;
    }

    //------------------------------qcarcam get frame--------------------------------
    QCarCamFrameInfo_t frameInfo;
    uint64_t memHndl;
    int time = 0;
    cv::Mat img;
    
    while(1) {
        ret = QCarCamGetFrame(hndl, &frameInfo, 100, 0);

        if(ret != QCARCAM_RET_OK) {
            std::cout << "QCarCamGetFrame failed" << std::endl;
        } else {
            bufferManager.getMemHndl(frameInfo.id, frameInfo.bufferIndex, 0, &memHndl);
            std::cout << time << " G Frame id : " << bufferManager.getDescription(frameInfo, 0) << std::endl;
            std::string file = "./sample_snapshot/snapshot_" + std::to_string(*reinterpret_cast<int*>(memHndl)) + ".bmp";

            img = cv::imread(file);

            if(img.empty()) {
                std::cerr << "Image load failed" << std::endl;
                return -1;
            }

            cv::namedWindow("image");
            cv::imshow("image", img);
            
            int key = cv::waitKey(16);
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            if(key == 'q') {
                cv::destroyAllWindows();
                return 0;
            }

            ++time;
        }

        ret = QCarCamReleaseFrame(hndl, frameInfo.id, frameInfo.bufferIndex);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10000));

    // //---------------------------qcarcam pause streaming-------------------------------
    // ret = QCarCamPause(hndl);
    // if(ret != QCARCAM_RET_OK) {
    //     std::cout << "QCarCamPause failed" << std::endl;
    // } else {
    //     std::cout << "QCarCamPause success" << std::endl;
    // }

    // //---------------------------qcarcam resume streaming-------------------------------
    // ret = QCarCamResume(hndl);
    // if(ret != QCARCAM_RET_OK) {
    //     std::cout << "QCarCamResume failed" << std::endl;
    // } else {
    //     std::cout << "QCarCamResume success" << std::endl;
    // }

    // //---------------------------qcarcam get frame-----------------------------------
    // for(uint32_t i = 0; i < 100; ++i) {
    //     ret = QCarCamGetFrame(hndl, &frameInfo, 100, 0);

    //     if(ret != QCARCAM_RET_OK) {
    //         std::cout << "QCarCamGetFrame failed" << std::endl;
    //     } else {
    //         std::cout << "G Frame id : " << bufferManager.getDescription(frameInfo, 0) << std::endl;
    //     }


    //     if(ret != QCARCAM_RET_OK) {
    //         std::cout << "QCarCamReleaseFrame failed" << std::endl;
    //     } else {
    //         std::cout << "R Frame id : " << bufferManager.getDescription(frameInfo, 0) << std::endl;
    //     }
    //     ret = QCarCamReleaseFrame(hndl, frameInfo.id, frameInfo.bufferIndex);
    // }

    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // //---------------------------qcarcam stop streaming---------------------------------
    // ret = QCarCamStop(hndl);
    // if(ret != QCARCAM_RET_OK) {
    //     std::cout << "QCarCamStop failed" << std::endl;
    // } else {
    //     std::cout << "QCarCamStop success" << std::endl;
    // }

    //-----------------------------end test----------------------------------------------
    std::cout << "End QCarCam API test" << std::endl;

    return 0;
}