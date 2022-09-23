/*! ***********************************************************************************************
 *
 * \file        client.h
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


class client
{
public:
    client(asio::io_context &ctx );

    void start(const std::string &host, const std::string &port);

private:
    void handle_resolve(const asio::error_code &err, const tcp::resolver::results_type &endpoints);

private:
    tcp::resolver resolver_;
    tcp::socket socket_;
};
