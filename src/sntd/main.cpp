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
#include <RCF/RCF.hpp>
#include <RCF/ProxyEndpoint.hpp>

#include "service.h"


static RCF::RcfServer *g_server = nullptr;

RCF::ProxyEndpoint makeProxyEndpoint(const std::string &client_id)
{
    assert(g_server);
    return RCF::ProxyEndpoint(*g_server, client_id);
}


int main(int argc, char *argv[])
{
    try
    {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);
        spdlog::set_default_logger(std::make_shared<spdlog::logger>("sntd", console_sink));
        spdlog::set_level(spdlog::level::debug);
        spdlog::info("Started.");

        const auto config = YAML::LoadFile("config.yaml");
        const auto core = config["server"];
        const auto host = core["host"].as<std::string>();
        const auto port = core["port"].as<uint16_t>();
        spdlog::info("Listening on {}:{}", host, port);

        // Initialize RCF.
        RCF::RcfInit rcfInit;

        // Instantiate a RCF server.
        RCF::RcfServer server(RCF::TcpEndpoint(host, port));
        server.setEnableProxyEndpoints(true);

        // Bind the interface
        service svc;
        server.bind<snt::sntd_service_interface>(svc);

        // Start the server
        server.start();

        spdlog::info("Press Enter to exit...");
        std::cin.get();
        spdlog::info("Exit.");
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
