#include <cstdint>
#include <iostream>
#include <cstdint>
#include <thread>
#include "qcarcam.h"
#include "input_manager.h"
#include "test_mode.h"
#include "handle_manager.h"
#include "stream_manager.h"
#include "qcarcam.h"

#ifndef __QCARCAM_API_H_
#define __QCARCAM_API_H_
QCarCamRet_e QCarCamInitialize(const QCarCamInit_t* pInitParams);

QCarCamRet_e QCarCamQueryInputs(QCarCamInput_t *pInputs, const uint32_t size, uint32_t *pRetSize);

QCarCamRet_e QCarCamQueryInputModes(const uint32_t inputId, QCarCamInputModes_t* pInputModes);

QCarCamRet_e QCarCamOpen(const QCarCamOpen_t* pOpenParams, QCarCamHndl_t* pHndl);

QCarCamRet_e QCarCamSetBuffers(const QCarCamHndl_t handle, const QCarCamBufferList_t* pBuffers);

QCarCamRet_e QCarCamStart(const QCarCamHndl_t hndl);

QCarCamRet_e QCarCamGetFrame(const QCarCamHndl_t hndl, QCarCamFrameInfo_t *pFrameInfo, const uint64_t timeout, const uint32_t flags);

QCarCamRet_e QCarCamReleaseFrame(const QCarCamHndl_t hndl, uint32_t id, uint32_t bufferIndex);

QCarCamRet_e QCarCamStop(const QCarCamHndl_t hndl);

QCarCamRet_e QCarCamPause(const QCarCamHndl_t hndl);

QCarCamRet_e QCarCamResume(const QCarCamHndl_t hndl);

#endif