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
#include <flatbuffers/flatbuffer_builder.h>


namespace snt {

/// 用于命令消息的 Magic 数
static const uint32_t COMMAND_MAGIC = 0xb8cba0ef;

/// 用于数据消息的 Magic 数
static const uint32_t DATA_MAGIC = 0xb0beae2c;


#pragma pack(push, 4)

/// 基本消息结构
struct message_t
{
    /// Magic 数，必须为 `COMMAND_MAGIC` 或 `DATA_MAGIC`
    uint32_t magic;
    /// 结构体总大小，字节
    uint32_t size;
};

/// 需要校验的消息结构
struct command_message_t : message_t
{
    /// 整个消息的 HMAC-SHA256 校验和，计算时用 0 填充
    uint8_t checksum[32];
    /// 消息数据
    uint8_t body[1];
};

#pragma pack(pop)


/*!
 * @brief 设置用于计算校验和的键。
 *
 * @param[in]   key         键数据
 * @param[in]   size        键长度，字节
*/
void set_checksum_key(const void *key, size_t size);

/*!
 * @brief 验证消息校验和。
 *
 * @param[in]   message     要验证的消息
 *
 * @return 如果校验和一致，则返回 `true`；否则返回 `false`。
*/
bool verify_checksum(const command_message_t *message);


/*!
 * @brief 计算消息的校验和。
 *
 * @param[in]   message     要计算的消息
*/
void sign(command_message_t *message);


size_t build_command_message(uint8_t *out, size_t size, const flatbuffers::FlatBufferBuilder &builder);

uint32_t get_body_size(const command_message_t *cmd);


}   // namespace snt
