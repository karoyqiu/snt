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

#include <yaml-cpp/yaml.h>


client::client(std::string &&id)
    : id_(std::move(id))
{}


void client::listen(const YAML::Node &config, snt::RcfClient<snt::sntd_service_interface> *sntd)
{
    const auto listenConfigs = config["listen"];
    assert(listenConfigs.IsSequence());

    for (const auto &lc : listenConfigs)
    {
        const auto rport = lc["remote_port"].as<uint16_t>();
        const auto tunnel_id = sntd->listen(snt::TCP, rport);
        spdlog::info("Tunnel ID for remote port {} is {}", rport, tunnel_id);

        remote_address raddr;
        raddr.host = lc["local_host"].as<std::string>();
        raddr.port = lc["local_port"].as<uint16_t>();
        tunnels_.emplace(tunnel_id, raddr);
    }
}


uint32_t client::connect(uint32_t tunnel_id)
{
    return 54321;
}


size_t client::send(uint32_t conn_id, const RCF::ByteBuffer &data)
{
    return data.getLength();
}
