/*! ***********************************************************************************************
 *
 * \file        messages.h
 * \brief       公共数据结构
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <cstdint>
#include <RCF/RCF.hpp>

#include "sntcommon_export.h"


namespace snt {

/// 用于命令消息的 Magic 数
static const uint32_t COMMAND_MAGIC = 0xb8cba0ef;

/// 用于数据消息的 Magic 数
static const uint32_t DATA_MAGIC = 0xb0beae2c;


enum Protocol {
    INVALID,
    TCP,
};


// sntd 服务
RCF_BEGIN(sntd_service_interface, "sntd_service")
    RCF_METHOD_R0(std::string, hello)
    RCF_METHOD_R2(uint32_t, listen, Protocol, uint16_t)
    RCF_METHOD_V3(void, connected, uint32_t, uint32_t, int)
    RCF_METHOD_R3(size_t, send, uint32_t, uint32_t, RCF::ByteBuffer)
RCF_END(sntd_service_interface)

// sntc 服务
RCF_BEGIN(sntc_service_interface, "sntc_service")
    RCF_METHOD_R1(uint32_t, connect, uint32_t)
    RCF_METHOD_R2(size_t, send, uint32_t, RCF::ByteBuffer)
RCF_END(sntc_service_interface)


}   // namespace snt
