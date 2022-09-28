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

#include "listen_session.h"
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

    auto listener = std::make_shared<listen_session>(s->client_id, protocol, port);
    listeners_.emplace(s->client_id, listener);

    return listener->channel_id();
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
