/*! ***********************************************************************************************
 *
 * \file        listener.cpp
 * \brief       监听会话
 *
 * \version     0.1
 * \date        2022/09/23
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "listener.h"

#include <cassert>
#include <RCF/ProxyEndpoint.hpp>

RCF::ProxyEndpoint makeProxyEndpoint(const std::string &client_id);

std::atomic_uint32_t listener::seq_(0);


listener::listener(const std::string &client_id, snt::Protocol protocol, uint16_t port)
    : channel_id_(++seq_)
    , logger_(client_id + "-CH" + std::to_string(channel_id_))
    , client_id_(client_id)
    , client_(std::make_shared<client_t>(makeProxyEndpoint(client_id)))
    , acceptor_(ctx_, tcp::endpoint(asio::ip::address_v4::any(), port))
    , socket_(ctx_)
{
    assert(!client_id.empty() && protocol == snt::TCP && port != 0);
    logger_.info("Listening on port {}", port);
    do_accept();
}


listener::~listener()
{
    logger_.info("Listening ended");
}


void listener::do_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec)
        {
            if (!ec)
            {
                auto conn_id = client_->connect(channel_id_);

                if (conn_id == 0)
                {
                    socket_.close();
                }
                else
                {

                }
            }

            do_accept();
        });
}
