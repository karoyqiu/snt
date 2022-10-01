/*! ***********************************************************************************************
 *
 * \file        remote_session.h
 * \brief       远程会话
 *
 * \version     0.1
 * \date        2022/09/30
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <atomic>
#include <memory>
#include <RCF/external/asio/asio.hpp>

#include "keyed_logger.h"

using asio::ip::tcp;

struct remote_address
{
    std::string host;
    std::string port;
};


class remote_session : public std::enable_shared_from_this<remote_session>
{
public:
    remote_session(uint32_t tunnel_id, const remote_address &addr);
    virtual ~remote_session();

    uint32_t id() const { return conn_id_; }

    void write(const char *buffer, size_t size);

private:
    void handle_connect(const asio::error_code &err);

    void do_read();
    void handle_read(const asio::error_code &err, size_t size);

private:
    static std::atomic_uint32_t seq_;
    const remote_address addr_;
    const uint32_t tunnel_id_;
    const uint32_t conn_id_;
    const keyed_logger logger_;
    asio::io_service ios_;
    tcp::resolver resolver_;
    tcp::socket socket_;
    std::unique_ptr<std::thread> thread_;
    char rbuf_[1024];
    char wbuf_[1024];
};

using remote_session_ptr = std::shared_ptr<remote_session>;
