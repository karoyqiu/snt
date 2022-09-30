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
#pragma once
#include <atomic>
#include <unordered_map>

#include "messages.h"

namespace YAML {
class Node;
}

struct remote_address
{
    std::string host;
    uint16_t port = 0;
};


class client
{
public:
    explicit client(std::string &&id);

    const std::string &id() const { return id_; }

    void listen(const YAML::Node &config, snt::RcfClient<snt::sntd_service_interface> *sntd);

    uint32_t connect(uint32_t tunnel_id);

    size_t send(uint32_t conn_id, const RCF::ByteBuffer &data);

private:
    const std::string id_;
    std::unordered_map<uint32_t, remote_address> tunnels_;
};
