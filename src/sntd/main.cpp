/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief       sntd 主源文件。
 *
 * \version     0.1
 * \date        2022-9-21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "server.h"


int main(int argc, char *argv[])
{
    std::cout << "Hello!" << std::endl;

    try
    {
        const auto config = YAML::LoadFile("config.yaml");
        const auto &core = config["core"];
        const auto host = core["host"].as<std::string>();
        const auto port = core["port"].as<uint16_t>();
        std::cout << "Listening on " << host << ":" << port << std::endl;

        asio::io_context ctx;
        server s(ctx, host, port);
        ctx.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
