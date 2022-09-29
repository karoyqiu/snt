/*! ***********************************************************************************************
 *
 * \file        session_manager.h
 * \brief       会话管理器类
 *
 * \version     0.1
 * \date        2022/09/29
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once


class session_manager
{
public:
    virtual ~session_manager() = default;
    virtual void remove(uint32_t conn_id) = 0;
};
