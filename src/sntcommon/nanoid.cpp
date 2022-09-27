/*! ***********************************************************************************************
 *
 * \file        nanoid.cpp
 * \brief       nanoid - 从 nanoid cpp 抄的
 *
 * \version     0.1
 * \date        2022/09/27
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "nanoid.h"

#ifdef _MSC_VER
#include <intrin.h>
#endif

#include <cassert>

#include "crypto_random.h"

static const std::string DEFAULT_DICT("_-0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
static const size_t DEFAULT_LENGTH = 21;


static int32_t clz32(int32_t x)
{
#ifdef _MSC_VER
    return __lzcnt(x);
#else
    // compile time constant
    const int32_t numIntBits = sizeof(int32_t) * 8;

    // do the smearing
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;

    // count the ones
    x -= x >> 1 & 0x55555555;
    x = (x >> 2 & 0x33333333) + (x & 0x33333333);
    x = (x >> 4) + x & 0x0f0f0f0f;
    x += x >> 8;
    x += x >> 16;

    return numIntBits - (x & 0x0000003f); //subtract # of 1s from 32
#endif
}


std::string nanoid()
{
    return nanoid(DEFAULT_DICT, DEFAULT_LENGTH);
}


std::string nanoid(const std::string &alphabet)
{
    return nanoid(alphabet, DEFAULT_LENGTH);
}


std::string nanoid(size_t length)
{
    return nanoid(DEFAULT_DICT, length);
}


std::string nanoid(const std::string &alphabet, size_t length)
{
    const auto alphabet_length = alphabet.length();
    assert(alphabet_length > 0 && alphabet_length < 255);
    assert(length > 0);

    // See https://github.com/ai/nanoid/blob/main/index.js for
    // explanation why masking is use (`random % alphabet` is a common
    // mistake security-wise).
    const size_t mask = (2 << (31 - clz32(static_cast<int32_t>((alphabet_length - 1) | 1)))) - 1;
    const auto step = static_cast<size_t>(std::ceil(1.6 * mask * length / alphabet_length));

    std::string id(length, '_');
    auto bytes = std::make_unique<uint8_t[]>(step);
    size_t count = 0;
    crypto_random random;

    for (;;)
    {
        random.next_bytes(bytes.get(), step);

        for (size_t i = 0; i < step; i++)
        {
            auto index = bytes[i] & mask;

            if (index < alphabet_length)
            {
                id[count++] = alphabet[index];

                if (count == length)
                {
                    return id;
                }
            }
        }
    }
}
