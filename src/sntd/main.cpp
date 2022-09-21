﻿/*! ***********************************************************************************************
 *
 * \file        main.cpp
 * \brief       sntd 主源文件。
 *
 * \version     0.1
 * \date        2022-9-21
 *
 * \author      Roy QIU <karoyqiu@gmail.com>
 * \copyright   © 2022 Roy QIU。
 *
 **************************************************************************************************/
#include <iostream>

#include "server.h"


int main(int argc, char *argv[])
{
    std::cout << "Hello!" << std::endl;

    try
    {
        asio::io_context ctx;
        server s(ctx, 8849);
        ctx.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "EXCEPTION: " << e.what() << std::endl;
    }

    return 0;
}
