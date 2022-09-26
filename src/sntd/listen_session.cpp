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

#include <sntrequest_generated.h>
#include <sntresponse_generated.h>

#include "session.h"

std::atomic_uint32_t listen_session::seq_(0);


listen_session::listen_session(session *parent, snt::Protocol protocol, uint16_t port)
    : parent_(parent)
    , acceptor_(ctx_, tcp::endpoint(asio::ip::address_v4::any(), port))
    , socket_(ctx_)
    , channel_id_(++seq_)
{
    assert(parent && protocol == snt::Protocol_Tcp && port != 0);
    spdlog::info("Listening channel {} on port {}", channel_id_, port);
    do_accept();

    flatbuffers::FlatBufferBuilder builder;
    auto head = snt::CreateHead(builder, 0, 0, 0);
    auto body = snt::CreateListenResponse(builder, channel_id_);
    auto resp = snt::CreateResponse(builder, head, snt::ResponseBody_ListenResponse, body.Union());
    builder.Finish(resp);

    parent->send_response(builder);
}


listen_session::~listen_session()
{
    spdlog::info("Listening channel {} ended", channel_id_);
}


void listen_session::do_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec)
        {
            if (!ec)
            {
                flatbuffers::FlatBufferBuilder builder;
                auto head = snt::CreateHead(builder, 0, 0, 0);
                auto body = snt::CreateConnectRequest(builder, channel_id_);
                auto resp = snt::CreateResponse(builder, head, snt::ResponseBody_ListenResponse, body.Union());
                builder.Finish(resp);

                parent_->send_response(builder);
            }

            do_accept();
        });
}
