/*! ***********************************************************************************************
 *
 * \file        listen_session.h
 * \brief       监听会话
 *
 * \version     0.1
 * \date        2022/09/23
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include <atomic>
#include <memory>
#include <RCF/external/asio/asio.hpp>

#include "keyed_logger.h"
#include "messages.h"

using asio::ip::tcp;

//using client_ptr = std::shared_ptr<snt::RcfClient<sntc_service_interface>>;


class listen_session
{
public:
 	listen_session(const std::string &client_id, snt::Protocol protocol, uint16_t port);
    virtual ~listen_session();

    uint32_t channel_id() const { return channel_id_; }

private:
    void do_accept();
 	
private:
    static std::atomic_uint32_t seq_;

    const std::string client_id_;
    const uint32_t channel_id_;
    const keyed_logger logger_;
    asio::io_service ctx_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
};
