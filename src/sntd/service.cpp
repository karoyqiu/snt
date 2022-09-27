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
#include "session.h"


void service::hello(const std::string &id)
{
    spdlog::info("Hello from {}", id);

    auto &rcfSession = RCF::getCurrentRcfSession();
    auto &s = rcfSession.getSessionObject<session>(true);
    s.client_id = id;
}


uint32_t service::listen(snt::Protocol protocol, uint16_t port)
{
    return 12345;
}
