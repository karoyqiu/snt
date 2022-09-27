/*! ***********************************************************************************************
 *
 * \file        crypto_random.cpp
 * \brief       随机数生成器 - 从 nanoid cpp 抄的
 *
 * \version     0.1
 * \date        2022/09/27
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "crypto_random.h"


crypto_random::crypto_random()
    : gen_(std::random_device()())
{}


void crypto_random::next_bytes(uint8_t *buffer, size_t size)
{
    using result_type = std::default_random_engine::result_type;

    size_t reps = (size / sizeof(result_type)) * sizeof(result_type);
    size_t i = 0;

    for (; i < reps; i += sizeof(result_type))
    {
        *(result_type *)(buffer + i) = gen_();
    }

    if (i == size)
    {
        return;
    }

    result_type last = gen_();

    for (; i < size; ++i)
    {
        *(buffer + i) = (uint8_t)((last >> (8 * (i - reps))));
    }
}
