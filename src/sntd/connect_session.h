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

#include "keyed_logger.h"
#include "messages.h"

using asio::ip::tcp;
using sntc_t = snt::RcfClient<snt::sntc_service_interface>;
using sntc_ptr = std::shared_ptr<sntc_t>;

class session_manager;


class connect_session : public std::enable_shared_from_this<connect_session>
{
public:
    connect_session(session_manager *manager, sntc_ptr client, uint32_t conn_id, tcp::socket &&s);

    void start();
    void write(const uint8_t *buffer, size_t size);

private:
    void do_read();
    void handle_read(const asio::error_code &err, std::size_t bytes_transferred);
    void handle_write(const asio::error_code &err, std::size_t bytes_transferred);

private:
    const keyed_logger logger_;
    const uint32_t conn_id_;
    session_manager *manager_;
    sntc_ptr client_;
    tcp::socket socket_;
    char buffer_[1024 * 4];
};
