/*! ***********************************************************************************************
 *
 * \file        client.h
 * \brief       服务类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "client.h"


client::client(std::string &&id)
    : id_(std::move(id))
{}


uint32_t client::connect(uint32_t tunnel_id)
{
    return 54321;
}


size_t client::send(uint32_t conn_id, const RCF::ByteBuffer &data)
{
    return data.getLength();
}
