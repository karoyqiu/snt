/*! ***********************************************************************************************
 *
 * \file        crypto_random.h
 * \brief       随机数生成器 - 从 nanoid cpp 抄的
 *
 * \version     0.1
 * \date        2022/09/27
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include <random>

#include "sntcommon_export.h"


class SNTCOMMON_EXPORT crypto_random
{
public:
    crypto_random();

    void next_bytes(uint8_t *buffer, size_t size);

private:
    std::default_random_engine gen_;
};
