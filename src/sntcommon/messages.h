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
#include <boost/predef/other/endian.h>

#if BOOST_ENDIAN_BIG_WORD || BOOST_ENDIAN_BIG_BYTE
#error Big-endian is not supported.
#endif


namespace snt {

/// Magic 数
static const uint32_t MAGIC = 0xb8cba0ef;


#pragma pack(push, 4)

/// 命令
enum class command_t : uint32_t
{
    /// 无效
    INVALID,
    /// 监听端口
    LISTEN,
    /// 连接服务器
    CONNECT,
};

/// 基本消息结构
struct message_t
{
    /// Magic 数，必须为 `MAGIC`
    uint32_t magic;
    /// 结构体总大小，字节
    uint32_t size;
    /// 消息序号
    uint32_t seq;
    /// 命令
    command_t command;
};

/// 需要校验的消息结构
struct checksum_message_t : message_t
{
    /// 整个消息的 HMAC-SHA256 校验和，计算时用 0 填充
    uint8_t checksum[32];
};

/// 支持的连接协议
enum class protocol_t : uint32_t
{
    /// 无效
    INVALID,
    /// 服务端监听 TCP 端口
    TCP,
};

/// 监听端口消息
struct listen_request_t : checksum_message_t
{
    /// 监听协议
    protocol_t protocol;
    /// 监听端口
    uint16_t port;
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
bool verify_checksum(const checksum_message_t *message);


/*!
 * @brief 计算消息的校验和。
 *
 * @param[in]   message     要计算的消息
*/
void sign(checksum_message_t *message);


}   // namespace snt
