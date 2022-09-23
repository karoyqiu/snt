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
#include <asio.hpp>

#include "messages.h"

using asio::ip::tcp;

class session;


class listen_session
 {
 public:
 	listen_session(session *parent, snt::protocol_t protocol, uint16_t port);

 private:
     void do_accept();
 	
 private:
     session *parent_;
     asio::io_context ctx_;
     tcp::acceptor acceptor_;
     tcp::socket socket_;
};
