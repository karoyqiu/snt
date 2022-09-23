/*! ***********************************************************************************************
 *
 * \file        session.cpp
 * \brief       会话类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "session.h"

#include "messages.h"
#include "listen_session.h"


session::session(tcp::socket &&socket)
    : socket_(std::move(socket))
    , seq_(0)
{
    memset(data_, 0, sizeof(data_));
}


session::~session()
{
    for (auto *s : listeners_)
    {
        delete s;
    }
}


void session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, sizeof(data_)),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (ec)
            {
                return;
            }

            // 主会话的消息总是带校验和
            const auto *msg = reinterpret_cast<snt::checksum_message_t *>(data_);

            if (msg->magic != snt::MAGIC || !snt::verify_checksum(msg))
            {
                return;
            }

            switch (msg->command)
            {
            
            case snt::command_t::LISTEN:
            {
                const auto *lm = static_cast<const snt::listen_request_t *>(msg);
                auto *l = new listen_session(this, lm->protocol, lm->port);
                listeners_.push_back(l);
                do_write(msg->size);
                break;
            }

            case snt::command_t::CONNECT:
                break;
            default:
                break;
            }
        }
    );
}


void session::do_write(size_t length)
{
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                do_read();
            }
        }
    );
}
