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

#include "connect_session.h"

RCF::ProxyEndpoint makeProxyEndpoint(const std::string &client_id);

std::atomic_uint32_t listener::seq_(0);


listener::listener(const std::string &client_id, snt::Protocol protocol, uint16_t port)
    : tunnel_id_(++seq_)
    , logger_(client_id + "-CH" + std::to_string(tunnel_id_))
    , client_id_(client_id)
    , client_(std::make_shared<sntc_t>(makeProxyEndpoint(client_id)))
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


size_t listener::send(uint32_t conn_id, const RCF::ByteBuffer &data)
{
    auto iter = sessions_.find(conn_id);

    if (iter != sessions_.end())
    {
        iter->second->write(reinterpret_cast<uint8_t *>(data.getPtr()), data.getLength());
        return data.getLength();
    }

    return 0;
}


void listener::remove(uint32_t conn_id)
{
    sessions_.erase(conn_id);
}


void listener::do_accept()
{
    acceptor_.async_accept(socket_, [this](const std::error_code &ec)
        {
            if (!ec)
            {
                auto conn_id = client_->connect(tunnel_id_);

                if (conn_id == 0)
                {
                    socket_.close();
                }
                else
                {
                    auto s = std::make_shared<connect_session>(this, client_, conn_id, std::move(socket_));
                    sessions_.emplace(conn_id, s);
                }
            }

            do_accept();
        });
}
