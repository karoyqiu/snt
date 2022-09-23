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


listen_session::listen_session(session *parent, snt::protocol_t protocol, uint16_t port)
    : parent_(parent)
    , acceptor_(ctx_, tcp::endpoint(asio::ip::address_v4::any(), port))
    , socket_(ctx_)
{
    assert(parent && protocol == snt::protocol_t::TCP && port != 0);
    do_accept();
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
