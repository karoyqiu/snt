﻿/*! ***********************************************************************************************
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
#pragma once


class client
{
public:
    explicit client(std::string &&id);

    const std::string &id() const { return id_; }

    uint32_t connect(uint32_t tunnel_id);

    size_t send(uint32_t conn_id, const RCF::ByteBuffer &data);

private:
    const std::string id_;
};
