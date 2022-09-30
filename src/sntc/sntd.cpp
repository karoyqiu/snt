/*! ***********************************************************************************************
 *
 * \file        sntd.cpp
 * \brief       sntd
 *
 * \version     0.1
 * \date        2022/09/30
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include "sntd.h"

static sntd_ptr g_sntd = nullptr;


void set_sntd(sntd_ptr p)
{
    g_sntd = p;
}


sntd_ptr get_sntd()
{
    return g_sntd;
}
