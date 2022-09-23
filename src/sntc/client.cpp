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
#include "client.h"


client::client(asio::io_context& ctx)
    : resolver_(ctx)
    , socket_(ctx)
{
}


void client::start(const std::string &host, const std::string &port)
{
    resolver_.async_resolve(host, port, std::bind(&client::handle_resolve, this,
        std::placeholders::_1, std::placeholders::_2));
}


void client::handle_resolve(const asio::error_code &err, const tcp::resolver::results_type &endpoints)
{

}
