/*! ***********************************************************************************************
 *
 * \file        messages.cpp
 * \brief       消息相关结构体。
 *
 * \version     0.1
 * \date        2022/09/23
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "messages.h"
//
//#include <openssl/hmac.h>
//#include <cassert>
//#include <memory>
//
//
//namespace snt {
//
//static std::unique_ptr<uint8_t[]> g_key;
//static size_t g_key_size = 0;
//
//
//void set_checksum_key(const void *key, size_t size)
//{
//    g_key = std::make_unique<uint8_t[]>(size);
//    memcpy(g_key.get(), key, size);
//    g_key_size = size;
//}
//
//
//bool verify_checksum(const command_message_t *message)
//{
//    auto buffer = std::make_unique<uint8_t[]>(message->size);
//    auto *copy = reinterpret_cast<command_message_t *>(buffer.get());
//    memcpy(copy, message, message->size);
//    sign(copy);
//
//    return memcmp(copy->checksum, message->checksum, sizeof(copy->checksum)) == 0;
//}
//
//
//void sign(command_message_t *message)
//{
//    memset(message->checksum, 0, sizeof(message->checksum));
//
//    // 计算 HMAC SHA256
//    auto *input = reinterpret_cast<const uint8_t *>(message);
//    uint8_t output[EVP_MAX_MD_SIZE] = { 0 };
//    unsigned int output_length = EVP_MAX_MD_SIZE;
//    auto *p = HMAC(EVP_sha256(), g_key.get(), static_cast<int>(g_key_size), input,
//        message->size, output, &output_length);
//    assert(p && output_length == sizeof(message->checksum));
//    memcpy(message->checksum, p, output_length);
//}
//
//
//size_t build_command_message(uint8_t *out, size_t size, const flatbuffers::FlatBufferBuilder &builder)
//{
//    auto *msg = reinterpret_cast<snt::command_message_t *>(out);
//    msg->magic = snt::COMMAND_MAGIC;
//    msg->size = offsetof(snt::command_message_t, body) + builder.GetSize();
//
//    if (msg->size > size)
//    {
//        return 0;
//    }
//
//    memset(msg->checksum, 0, sizeof(msg->checksum));
//    memcpy(msg->body, builder.GetBufferPointer(), builder.GetSize());
//    snt::sign(msg);
//
//    return msg->size;
//}
//
//
//uint32_t get_body_size(const command_message_t *cmd)
//{
//    return cmd->size - offsetof(command_message_t, body);
//}
//
//
//}   // namespace snt
