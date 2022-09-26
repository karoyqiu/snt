/*! ***********************************************************************************************
 *
 * \file        session.cpp
 * \brief       会话类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "session.h"

#include <sntrequest_generated.h>
#include <sntresponse_generated.h>

#include "messages.h"
#include "listen_session.h"


session::session(tcp::socket &&socket)
    : socket_(std::move(socket))
    , seq_(0)
{
    spdlog::debug("Client session started: {}:{}", socket_.remote_endpoint().address().to_string(), socket_.remote_endpoint().port());
    memset(data_, 0, sizeof(data_));
}


session::~session()
{
    spdlog::debug("Client session ended: {}:{}", socket_.remote_endpoint().address().to_string(), socket_.remote_endpoint().port());

    for (auto *s : listeners_)
    {
        delete s;
    }
}


void session::send_response(const flatbuffers::FlatBufferBuilder &builder)
{
    auto self(shared_from_this());

    auto *msg = reinterpret_cast<snt::command_message_t *>(data_);
    msg->magic = snt::COMMAND_MAGIC;
    msg->size = offsetof(snt::command_message_t, body) + builder.GetSize();
    assert(msg->size <= MAX_LENGHT);
    memset(msg->checksum, 0, sizeof(msg->checksum));
    memcpy(msg->body, builder.GetBufferPointer(), builder.GetSize());
    snt::sign(msg);

    asio::async_write(socket_, asio::buffer(data_, msg->size),
        [this, self](const std::error_code &err, std::size_t /*length*/)
        {
            if (!err)
            {
                do_read();
            }
            else
            {
                spdlog::error("Failed to write: {}", err.message());
            }
        }
    );
}


void session::do_read()
{
    auto self(shared_from_this());
    socket_.async_read_some(asio::buffer(data_, sizeof(data_)),
        [this, self](const std::error_code &err, std::size_t length)
        {
            if (err)
            {
                spdlog::error("Failed to read: {}", err.message());
                return;
            }

            // 主会话的消息总是带校验和
            const auto *msg = reinterpret_cast<snt::message_t *>(data_);

            if (msg->magic != snt::COMMAND_MAGIC)
            {
                spdlog::error("Magic mismatch");
                return;
            }

            const auto *cmd = static_cast<const snt::command_message_t *>(msg);

            if (!snt::verify_checksum(cmd))
            {
                spdlog::error("Failed to verify checksum");
                return;
            }

            const auto body_size = snt::get_body_size(cmd);
            flatbuffers::Verifier verifier(cmd->body, body_size);

            if (!snt::VerifyRequestBuffer(verifier))
            {
                spdlog::error("Failed to verify buffer");
                return;
            }

            auto *req = snt::GetRequest(cmd->body);

            // UNDONE: 检查时间戳和随机数

            switch (req->body_type())
            {
            
            case snt::RequestBody_ListenRequest:
            {
                auto *body = req->body_as_ListenRequest();
                auto *l = new listen_session(this, body->protocol(), body->port());
                listeners_.push_back(l);
                do_write(msg->size);
                break;
            }

            default:
                spdlog::error("Unknown body type {}", req->body_type());
                break;
            }
        }
    );
}


void session::do_write(size_t length)
{
    auto self(shared_from_this());
    asio::async_write(socket_, asio::buffer(data_, length),
        [this, self](std::error_code ec, std::size_t /*length*/)
        {
            if (!ec)
            {
                do_read();
            }
        }
    );
}
