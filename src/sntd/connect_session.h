/*! ***********************************************************************************************
 *
 * \file        connect_session.h
 * \brief       远端会话
 *
 * \version     0.1
 * \date        2022/09/28
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <RCF/external/asio/asio.hpp>

#include "messages.h"

using asio::ip::tcp;
using client_ptr = std::unique_ptr<snt::RcfClient<snt::sntc_service_interface>>;


class connect_session
{
public:
    connect_session(const std::string &client_id, tcp::socket &&s);

private:
    client_ptr client_;
    tcp::socket socket_;
};
