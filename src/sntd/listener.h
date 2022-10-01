/*! ***********************************************************************************************
 *
 * \file        listener.h
 * \brief       监听会话
 *
 * \version     0.1
 * \date        2022/09/23
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "session_manager.h"

#include <atomic>
#include <memory>
#include <thread>
#include <unordered_map>
#include <RCF/external/asio/asio.hpp>

#include "keyed_logger.h"
#include "messages.h"

class connect_session;

using asio::ip::tcp;
using sntc_t = snt::RcfClient<snt::sntc_service_interface>;
using sntc_ptr = std::shared_ptr<sntc_t>;
using session_ptr = std::shared_ptr<connect_session>;


class listener : public session_manager
{
public:
    listener(const std::string &client_id, snt::Protocol protocol, uint16_t port);
    virtual ~listener();

    const std::string &client_id() const { return client_id_; }
    uint32_t tunnel_id() const { return tunnel_id_; }

    size_t send(uint32_t conn_id, const RCF::ByteBuffer &data);

    virtual void remove(uint32_t conn_id) override;

private:
    void do_accept();

private:
    static std::atomic_uint32_t seq_;

    const uint32_t tunnel_id_;
    const keyed_logger logger_;
    const std::string client_id_;
    sntc_ptr client_;
    std::unique_ptr<std::thread> thread_;
    asio::io_service ios_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;
    std::unordered_map<uint32_t, session_ptr> sessions_;
};
