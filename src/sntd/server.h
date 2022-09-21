/*! ***********************************************************************************************
 *
 * \file        server.h
 * \brief       服务类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <asio.hpp>

using asio::ip::tcp;


class server
{
public:
    server(asio::io_context& ctx, uint16_t port);

private:
    void do_accept();

private:
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};
