/*! ***********************************************************************************************
 *
 * \file        session.h
 * \brief       会话类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <atomic>
#include <memory>
#include <vector>
#include <asio.hpp>
#include <flatbuffers/flatbuffer_builder.h>

using asio::ip::tcp;

class listen_session;


class session : public std::enable_shared_from_this<session>
{
public:
    explicit session(tcp::socket&& socket);
    virtual ~session();

    void start() { do_read(); };

    void send_response(const flatbuffers::FlatBufferBuilder &builder);

private:
    void do_read();
    void do_write(size_t length);

private:
    tcp::socket socket_;
    std::atomic_uint32_t seq_;
    std::vector<listen_session *> listeners_;
    enum { MAX_LENGHT = 1024 * 2 };
    uint8_t data_[MAX_LENGHT];
};
