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
#include "server.h"
#include "session.h"


server::server(asio::io_context& ctx, const std::string &host, uint16_t port)
    : acceptor_(ctx, tcp::endpoint(asio::ip::make_address(host), port))
    , socket_(ctx)
{
    do_accept();
}


void server::do_accept()
{
    acceptor_.async_accept(socket_, [this](std::error_code ec)
        {
            if (!ec)
            {
                auto s = std::make_shared<session>(std::move(socket_));
                s->start();
            }

            do_accept();
        });
}
