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

#include <cassert>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include <sntrequest_generated.h>

#include "messages.h"

using std::placeholders::_1;
using std::placeholders::_2;


client::client(asio::io_context& ctx)
    : resolver_(ctx)
    , socket_(ctx)
{
}


void client::start(const std::string &host, const std::string &port)
{
    resolver_.async_resolve(host, port, std::bind(&client::handle_resolve, this, _1, _2));
}


void client::handle_resolve(const asio::error_code &err, const tcp::resolver::results_type &endpoints)
{
    if (!err)
    {
        asio::async_connect(socket_, endpoints, std::bind(&client::handle_connect, this, _1));
    }
    else
    {
        spdlog::error("Failed to resolve: {}", err.message());
    }
}


void client::handle_connect(const asio::error_code &err)
{
    if (!err)
    {
        const auto config = YAML::LoadFile("config.yaml");
        const auto &core = config["listen"];
        assert(core.IsSequence());

        const auto first = core[0];
        flatbuffers::FlatBufferBuilder builder;
        const auto head = snt::CreateHead(builder, 0, 0, 0);
        const auto body = snt::CreateListenRequest(builder, snt::Protocol_Tcp, first["port"].as<uint16_t>());
        const auto req = snt::CreateRequest(builder, head, snt::RequestBody_ListenRequest, body.Union());
        builder.Finish(req);

        uint8_t buffer[1024] = { 0 };
        auto size = snt::build_command_message(buffer, sizeof(buffer), builder);
        asio::async_write(socket_, asio::buffer(buffer, size), [this](const asio::error_code &err, std::size_t)
            {
                if (!err)
                {

                }
                else
                {
                    spdlog::error("Error: {}", err.message());
                }
            }
        );
    }
    else
    {
        spdlog::error("Failed to connect: {}", err.message());
    }
}
