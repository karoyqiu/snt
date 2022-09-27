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
    RCF_METHOD_V1(void, hello, const std::string &)
    RCF_METHOD_R2(uint32_t, listen, Protocol, uint16_t)
RCF_END(sntd_service_interface)

// sntc 服务
RCF_BEGIN(sntc_service_interface, "sntc_service")
    RCF_METHOD_R1(uint32_t, connect, uint32_t)
RCF_END(sntc_service_interface)

//
//#pragma pack(push, 4)
//
///// 基本消息结构
//struct message_t
//{
//    /// Magic 数，必须为 `COMMAND_MAGIC` 或 `DATA_MAGIC`
//    uint32_t magic;
//    /// 结构体总大小，字节
//    uint32_t size;
//};
//
///// 需要校验的消息结构
//struct command_message_t : message_t
//{
//    /// 整个消息的 HMAC-SHA256 校验和，计算时用 0 填充
//    uint8_t checksum[32];
//    /// 消息数据
//    uint8_t body[1];
//};
//
//#pragma pack(pop)
//
//
///*!
// * @brief 设置用于计算校验和的键。
// *
// * @param[in]   key         键数据
// * @param[in]   size        键长度，字节
//*/
//SNTCOMMON_EXPORT void set_checksum_key(const void *key, size_t size);
//
///*!
// * @brief 验证消息校验和。
// *
// * @param[in]   message     要验证的消息
// *
// * @return 如果校验和一致，则返回 `true`；否则返回 `false`。
//*/
//SNTCOMMON_EXPORT bool verify_checksum(const command_message_t *message);
//
//
///*!
// * @brief 计算消息的校验和。
// *
// * @param[in]   message     要计算的消息
//*/
//SNTCOMMON_EXPORT void sign(command_message_t *message);
//
//
//SNTCOMMON_EXPORT size_t build_command_message(uint8_t *out, size_t size, const flatbuffers::FlatBufferBuilder &builder);
//
//SNTCOMMON_EXPORT uint32_t get_body_size(const command_message_t *cmd);


}   // namespace snt
