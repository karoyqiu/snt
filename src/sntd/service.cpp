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
#include "service.h"

#include "nanoid.h"

#include "listener.h"
#include "session.h"


std::string service::hello()
{
    auto &rcfSession = RCF::getCurrentRcfSession();
    rcfSession.setOnDestroyCallback(std::bind(&service::clear_client, this, std::placeholders::_1));

    auto &s = rcfSession.getSessionObject<session>(true);
    s.client_id = nanoid();
    spdlog::info("Hello from {}", s.client_id);
    return s.client_id;
}


uint32_t service::listen(snt::Protocol protocol, uint16_t port)
{
    auto &rcfSession = RCF::getCurrentRcfSession();
    const auto *s = rcfSession.querySessionObject<session>();

    if (s == nullptr || s->client_id.empty())
    {
        spdlog::error("Listening without client ID");
        return 0;
    }

    auto l = std::make_shared<listener>(s->client_id, protocol, port);
    listeners_.emplace(s->client_id, l);

    return l->tunnel_id();
}


void service::connected(uint32_t tunnel_id, uint32_t conn_id, int error)
{
    auto l = find_listener(tunnel_id);

    if (l)
    {
        return l->start(conn_id);
    }
}


size_t service::send(uint32_t tunnel_id, uint32_t conn_id, const RCF::ByteBuffer &data)
{
    auto l = find_listener(tunnel_id);

    if (l)
    {
        return l->send(conn_id, data);
    }

    return 0;
}


void service::clear_client(RCF::RcfSession &rcfSession)
{
    const auto *s = rcfSession.querySessionObject<session>();

    if (s && !s->client_id.empty())
    {
        spdlog::info("Client disconnected: {}", s->client_id);
        listeners_.erase(s->client_id);
    }
}


listener_ptr service::find_listener(uint32_t tunnel_id) const
{
    auto &rcfSession = RCF::getCurrentRcfSession();
    const auto *s = rcfSession.querySessionObject<session>();

    if (s)
    {
        auto range = listeners_.equal_range(s->client_id);

        for (auto iter = range.first; iter != range.second; ++iter)
        {
            auto l = iter->second;

            if (l->tunnel_id() == tunnel_id)
            {
                return l;
            }
        }

    }

    return {};
}
