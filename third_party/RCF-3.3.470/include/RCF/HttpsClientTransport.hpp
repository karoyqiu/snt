
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

#ifndef INCLUDE_RCF_HTTPSCLIENTTRANSPORT_HPP
#define INCLUDE_RCF_HTTPSCLIENTTRANSPORT_HPP

#include <RCF/TcpClientTransport.hpp>

namespace RCF {

    class HttpsEndpoint;

    class RCF_EXPORT HttpsClientTransport : public TcpClientTransport
    {
    public:
        HttpsClientTransport(const HttpsEndpoint & httpsEndpoint);
        TransportType getTransportType();

    private:
        std::string mServerUrlPath;
    };

} // namespace RCF

#endif // ! INCLUDE_RCF_HTTPSCLIENTTRANSPORT_HPP
