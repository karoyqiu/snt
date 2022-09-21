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


session::session(tcp::socket &&socket)
    : socket_(std::move(socket))
{
    memset(data_, 0, sizeof(data_));
}


void session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, sizeof(data_)),
        [this, self](std::error_code ec, std::size_t length)
        {
            if (!ec)
            {
                do_write(length);
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
