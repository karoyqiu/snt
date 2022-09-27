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
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <yaml-cpp/yaml.h>
#include <RCF/RCF.hpp>
#include <RCF/ProxyEndpoint.hpp>

#include "messages.h"
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
        const auto core = config["server"];
        const auto host = core["host"].as<std::string>();
        const auto port = core["port"].as<uint16_t>();
        std::cout << "Connecting to " << host << ":" << port << std::endl;

        // Initialize RCF.
        RCF::RcfInit rcfInit;

        // Instantiate a RCF client.
        const RCF::TcpEndpoint endpoint(host, port);
        snt::RcfClient<snt::sntd_service_interface> sntc(endpoint);

        client c;
        sntc.hello(c.id());

        // Connect to the server and call the Print() method.
        const auto listenConfigs = config["listen"];
        assert(listenConfigs.IsSequence());

        for (const auto &lc : listenConfigs)
        {
            const auto rport = lc["remote_port"].as<uint16_t>();
            const auto tunnel_id = sntc.listen(snt::TCP, rport);
            spdlog::info("Tunnel ID for remote port {} is {}", rport, tunnel_id);
        }


        RCF::RcfServer clientServer(RCF::ProxyEndpoint(endpoint, c.id()));
        clientServer.bind<snt::sntc_service_interface>(c);
        clientServer.start();

        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
        spdlog::info("Exit.");
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
