/*! ***********************************************************************************************
 *
 * \file        sntd.h
 * \brief       sntd
 *
 * \version     0.1
 * \date        2022/09/30
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#pragma once
#include "messages.h"

using sntd_ptr = snt::RcfClient<snt::sntd_service_interface> *;

void set_sntd(sntd_ptr p);
sntd_ptr get_sntd();
