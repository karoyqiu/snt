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
#include "session.h"


std::string service::hello()
{
    auto &rcfSession = RCF::getCurrentRcfSession();
    auto &s = rcfSession.getSessionObject<session>(true);
    s.client_id = nanoid();
    spdlog::info("Hello from {}", s.client_id);
    return s.client_id;
}


uint32_t service::listen(snt::Protocol protocol, uint16_t port)
{
    return 12345;
}
