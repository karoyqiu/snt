/*! ***********************************************************************************************
 *
 * \file        service.h
 * \brief       服务类。
 *
 * \version     0.1
 * \date        2022/09/21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include "messages.h"


class service
{
public:
    void hello(const std::string &id);
    uint32_t listen(snt::Protocol protocol, uint16_t port);
};
