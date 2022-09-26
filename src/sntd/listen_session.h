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
#include <asio.hpp>

#include <sntcommon_generated.h>

using asio::ip::tcp;

class session;


class listen_session
 {
 public:
 	listen_session(session *parent, snt::Protocol protocol, uint16_t port);

    uint32_t channel_id() const { return channel_id_; }

 private:
     void do_accept();
 	
 private:
     static std::atomic_uint32_t seq_;

     session *parent_;
     asio::io_context ctx_;
     tcp::acceptor acceptor_;
     tcp::socket socket_;
     const uint32_t channel_id_;
};
