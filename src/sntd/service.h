/*! ***********************************************************************************************
 *
 * \file        service.h
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
#include <memory>
#include <unordered_map>

#include "messages.h"

class listener;
using listener_ptr = std::shared_ptr<listener>;


class service
{
public:
    std::string hello();

    uint32_t listen(snt::Protocol protocol, uint16_t port);

    void connected(uint32_t tunnel_id, uint32_t conn_id, int error);

    size_t send(uint32_t tunnel_id, uint32_t conn_id, const RCF::ByteBuffer &data);

private:
    void clear_client(RCF::RcfSession &rcfSession);

    listener_ptr find_listener(uint32_t tunnel_id) const;

private:
    std::unordered_multimap<std::string, listener_ptr> listeners_;
};
