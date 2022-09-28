/*! ***********************************************************************************************
 *
 * \file        connect_session.cpp
 * \brief       远端会话
 *
 * \version     0.1
 * \date        2022/09/28
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "connect_session.h"

#include <RCF/ProxyEndpoint.hpp>

#include "messages.h"

RCF::ProxyEndpoint makeProxyEndpoint(const std::string &client_id);


connect_session::connect_session(const std::string &client_id, tcp::socket &&s)
    : client_(std::make_unique<snt::RcfClient<snt::sntc_service_interface>>(makeProxyEndpoint(client_id)))
    , socket_(std::move(s))
{

}
