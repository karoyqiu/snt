/*! ***********************************************************************************************
 *
 * \file        nanoid.h
 * \brief       nanoid - 从 nanoid cpp 抄的
 *
 * \version     0.1
 * \date        2022/09/27
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include "sntcommon_export.h"

SNTCOMMON_EXPORT std::string nanoid();

SNTCOMMON_EXPORT std::string nanoid(const std::string &alphabet);

SNTCOMMON_EXPORT std::string nanoid(size_t length);

SNTCOMMON_EXPORT std::string nanoid(const std::string &alphabet, size_t length);
