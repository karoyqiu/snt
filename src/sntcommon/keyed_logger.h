/*! ***********************************************************************************************
 *
 * \file        keyed_logger.h
 * \brief       带键的日志记录器类。
 *
 * \version     0.1
 * \date        2022/09/26
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <spdlog/spdlog.h>

static const std::string prefix_("<{}> ");


class keyed_logger
{
public:
    explicit keyed_logger(const std::string &key) : key_(key) {}
    explicit keyed_logger(std::string &&key) : key_(std::move(key)) {}

    template<typename... Args>
    inline void trace(const char *fmt, Args &&... args) const
    {
        spdlog::trace(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void debug(const char *fmt, Args &&... args) const
    {
        spdlog::debug(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void info(const char *fmt, Args &&... args) const
    {
        spdlog::info(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void warn(const char *fmt, Args &&... args) const
    {
        spdlog::warn(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void error(const char *fmt, Args &&... args) const
    {
        spdlog::error(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    template<typename... Args>
    inline void critical(const char *fmt, Args &&... args) const
    {
        spdlog::critical(prefix_ + fmt, key_, std::forward<Args>(args)...);
    }

    inline void trace(const char *msg) const
    {
        spdlog::trace(prefix_ + msg, key_);
    }

    inline void debug(const char *msg) const
    {
        spdlog::debug(prefix_ + msg, key_);
    }

    inline void info(const char *msg) const
    {
        spdlog::info(prefix_ + msg, key_);
    }

    inline void warn(const char *msg) const
    {
        spdlog::warn(prefix_ + msg, key_);
    }

    inline void error(const char *msg) const
    {
        spdlog::error(prefix_ + msg, key_);
    }

    inline void critical(const char *msg) const
    {
        spdlog::critical(prefix_ + msg, key_);
    }

private:
    const std::string key_;
};
