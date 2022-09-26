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
#include <spdlog/sinks/stdout_color_sinks.h>
#include <yaml-cpp/yaml.h>

#include "client.h"


int main(int argc, char *argv[])
{
    try
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);
        spdlog::set_default_logger(std::make_shared<spdlog::logger>("sntc", console_sink));
        spdlog::info("Started.");

        const auto config = YAML::LoadFile("config.yaml");
        const auto &core = config["server"];
        const auto host = core["host"].as<std::string>();
        const auto port = core["port"].as<std::string>();
        std::cout << "Connecting to " << host << ":" << port << std::endl;

        asio::io_context ctx;
        client c(ctx);

        c.start(host, port);
        ctx.run();

        spdlog::info("Exit.");
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
