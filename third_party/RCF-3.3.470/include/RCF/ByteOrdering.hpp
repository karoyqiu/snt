
//******************************************************************************
// RCF - Remote Call Framework
//
// Copyright (c) 2005 - 2022, Delta V Software. All rights reserved.
// https://www.deltavsoft.com
//
// RCF is distributed under dual licenses - closed source or GPL.
// Consult your particular license for conditions of use.
//
// If you have not purchased a commercial license, you are using RCF under GPL terms.
//
// Version: 3.3
// Contact: support <at> deltavsoft.com 
//
//******************************************************************************

#ifndef INCLUDE_RCF_BYTEORDERING_HPP
#define INCLUDE_RCF_BYTEORDERING_HPP

#include <RCF/Export.hpp>

namespace RCF {

    RCF_EXPORT void machineToNetworkOrder(void *buffer, int width, int count);
    RCF_EXPORT void networkToMachineOrder(void *buffer, int width, int count);
    RCF_EXPORT bool machineOrderEqualsNetworkOrder();
    RCF_EXPORT bool isPlatformLittleEndian();

} // namespace RCF

#endif // ! INCLUDE_RCF_BYTEORDERING_HPP
