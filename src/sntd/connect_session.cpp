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
#include "session_manager.h"

using std::placeholders::_1;
using std::placeholders::_2;

RCF::ProxyEndpoint makeProxyEndpoint(const std::string &client_id);


connect_session::connect_session(session_manager *manager, sntc_ptr client, uint32_t conn_id, tcp::socket &&s)
    : logger_("CONN" + std::to_string(conn_id))
    , conn_id_(conn_id)
    , manager_(manager)
    , client_(client)
    , socket_(std::move(s))
{
    do_read();
}


void connect_session::write(const uint8_t *buffer, size_t size)
{
    socket_.async_write_some(asio::buffer(buffer, size),
        std::bind(&connect_session::handle_write, shared_from_this(), _1, _2));
}


void connect_session::do_read()
{
    socket_.async_read_some(asio::buffer(buffer_),
        std::bind(&connect_session::handle_read, shared_from_this(), _1, _2));
}


void connect_session::handle_read(const asio::error_code &err, std::size_t bytes_transferred)
{
    if (!err)
    {
        client_->send(conn_id_, RCF::ByteBuffer(buffer_, bytes_transferred, true));
        do_read();
    }
    else
    {
        logger_.error("Failed to read: {}", err.message());
        manager_->remove(conn_id_);
    }
}


void connect_session::handle_write(const asio::error_code &err, std::size_t bytes_transferred)
{
    if (err)
    {
        logger_.error("Failed to write: {}", err.message());
        manager_->remove(conn_id_);
    }
}
