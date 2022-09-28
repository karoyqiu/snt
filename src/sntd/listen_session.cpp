/*! ***********************************************************************************************
 *
 * \file        listen_session.cpp
 * \brief       监听会话
 *
 * \version     0.1
 * \date        2022/09/23
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "listen_session.h"

#include <cassert>

std::atomic_uint32_t listen_session::seq_(0);


listen_session::listen_session(const std::string &client_id, snt::Protocol protocol, uint16_t port)
    : client_id_(client_id)
    , channel_id_(++seq_)
    , logger_(client_id + "-CH" + std::to_string(channel_id_))
    , acceptor_(ctx_, tcp::endpoint(asio::ip::address_v4::any(), port))
    , socket_(ctx_)
{
    assert(!client_id.empty() && protocol == snt::TCP && port != 0);
    logger_.info("Listening on port {}", port);
    do_accept();
}


listen_session::~listen_session()
{
    logger_.info("Listening ended");
}


void listen_session::do_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec)
        {
            if (!ec)
            {

            }

            do_accept();
        });
}
