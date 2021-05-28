//
// Created by kris on 2021-05-26.
//

#ifndef BALEURI_INCLUDE_AUTHORITY_H_
#define BALEURI_INCLUDE_AUTHORITY_H_

#include <boost/spirit/home/x3.hpp>
#include "UriUtils.h"

namespace x3 = boost::spirit::x3;

namespace bale::uri {

static const auto UserInfo = *(Unreserved | PercentEncoded | SubDelimiter | x3::char_(':'));
static const auto DecOctet = ((x3::string("25") >> x3::char_('0', '5')) |
    (x3::char_('2') >> x3::char_('0', '4') >> x3::digit) |
    (x3::char_('1') >> x3::repeat[2](x3::digit)) |
    (x3::char_('1', '9') >> x3::digit) | x3::digit);

static const auto IPv4Address = DecOctet >> x3::repeat[3](x3::char_('.') >> DecOctet);

static const auto
    h16 = (Hex >> x3::repeat[3](Hex)) | (Hex >> x3::repeat[2](Hex)) | (Hex >> Hex) | Hex; // possible x3::hex will work
static const auto ls32 = (h16 >> ':' >> h16) | IPv4Address;

static const auto IPv6Address =
    x3::repeat[6]((h16 >> ':')) >> ls32 |
        x3::string("::") >> x3::repeat[5]((h16 >> ':')) >> ls32 |
        -(h16) >> x3::string("::") >> x3::repeat[4]((h16 >> ':')) >> ls32 |
        -(h16 >> ':' >> h16) >> x3::string("::") >> x3::repeat[3]((h16 >> ':')) >> ls32 |
        -(x3::repeat[2]((h16 >> ':')) >> h16) >> x3::string("::") >> x3::repeat[2]((h16 >> ':')) >> ls32 |
        -(x3::repeat[3]((h16 >> ':')) >> h16) >> x3::string("::") >> (h16 >> ':') >> ls32 |
        -(x3::repeat[4]((h16 >> ':')) >> h16) >> x3::string("::") >> ls32 |
        -(x3::repeat[5]((h16 >> ':')) >> h16) >> x3::string("::") >> h16 |
        -(x3::repeat[6]((h16 >> ':')) >> h16) >> x3::string("::");

static const auto RegName = *(Unreserved | PercentEncoded | SubDelimiter);
static const auto Host = (IPv4Address | IPv6Address | RegName);
static const auto Port = *x3::digit;

static const auto Authority = -(UserInfo >> '@') >> Host >> -(':' >> Port);

}

#endif //BALEURI_INCLUDE_AUTHORITY_H_
