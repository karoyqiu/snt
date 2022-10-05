/*! ***********************************************************************************************
 *
 * \file        remote_session.cpp
 * \brief       远程会话
 *
 * \version     0.1
 * \date        2022/09/30
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "remote_session.h"

#include <RCF/ByteBuffer.hpp>

#include "sntd.h"

using std::placeholders::_1;
using std::placeholders::_2;

std::atomic_uint32_t remote_session::seq_(0);


remote_session::remote_session(uint32_t tunnel_id, const remote_address &addr)
    : addr_(addr)
    , tunnel_id_(tunnel_id)
    , conn_id_(++seq_)
    , logger_("TN" + std::to_string(tunnel_id) + "RS" + std::to_string(conn_id_))
    , resolver_(ios_)
    , socket_(ios_)
{
    logger_.info("Connecting to {}:{}", addr_.host, addr_.port);

    resolver_.async_resolve(tcp::resolver::query{ addr.host, addr.port },
        [this](const asio::error_code &err, const tcp::resolver::iterator &endpoints)
        {
            if (!err)
            {
                asio::async_connect(socket_, endpoints,
                    std::bind(&remote_session::handle_connect, shared_from_this(), _1));
            }
            else
            {
                logger_.error("Failed to resolve: {}", err.message());
                get_sntd()->close(tunnel_id_, conn_id_);
            }
        });

    thread_ = std::make_unique<std::thread>(
        std::bind(static_cast<size_t(asio::io_service:: *)()>(&asio::io_service::run), &ios_)
    );
}


remote_session::~remote_session()
{
    ios_.stop();

    if (thread_ && thread_->joinable())
    {
        thread_->join();
    }
}


void remote_session::close()
{
    socket_.close();
}


void remote_session::write(const char *buffer, size_t size)
{
    auto self = shared_from_this();

    assert(size <= sizeof(wbuf_));
    memcpy(wbuf_, buffer, size);

    asio::async_write(socket_, asio::buffer(wbuf_, size),
        [self](const asio::error_code &err, size_t size)
        {
            if (err)
            {
                self->logger_.error("Failed to write: {}", err.message());
                get_sntd()->close(self->tunnel_id_, self->conn_id_);
            }
        }
    );
}


void remote_session::handle_connect(const asio::error_code &err)
{
    if (!err)
    {
        logger_.info("Connected");
        get_sntd()->connected(tunnel_id_, conn_id_);
        do_read();
    }
    else
    {
        logger_.error("Failed to connect: {}", err.message());
        get_sntd()->close(tunnel_id_, conn_id_);
    }
}


void remote_session::do_read()
{
    socket_.async_read_some(asio::buffer(rbuf_, sizeof(rbuf_)),
        std::bind(&remote_session::handle_read, shared_from_this(), _1, _2));
}


void remote_session::handle_read(const asio::error_code &err, size_t size)
{
    if (!err)
    {
        get_sntd()->send(tunnel_id_, conn_id_, RCF::ByteBuffer(rbuf_, size, true));
        do_read();
    }
    else
    {
        logger_.error("Failed to read: {}", err.message());
        get_sntd()->close(tunnel_id_, conn_id_);
    }
}
