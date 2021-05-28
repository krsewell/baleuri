//
// Created by kris on 2021-05-21.
//

#ifndef BALEURI_INCLUDE_URIUTILS_H_
#define BALEURI_INCLUDE_URIUTILS_H_

#include <string>
#include <string_view>
#include <stdexcept>
#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace bale {
namespace uri {

typedef std::string::const_iterator sv_iterator;

template<typename T>
bool parse(const std::string_view, T);

bool isUnreserved(const std::string_view);

bool isGenDelimiter(const std::string_view);

bool isSubDelimiter(const std::string_view);

bool isReserved(const std::string_view);

bool isHex(const std::string_view);

bool percentDecoder(sv_iterator start, sv_iterator end, char &c);
[[unimplemented]]
bool percentEncoder(sv_iterator chara, std::string_view &str);

[[deprecated("Marked for deletion")]]
short toShort(const char c);
[[deprecated("Marked for deletion")]]
char toChar(short value);
[[deprecated("Marked for deletion")]]
short hexPair_toShort(const char msd, const char lsd);
[[deprecated("Marked for deletion")]]
std::string short_toHexPair(const short in);
[[deprecated("Marked for deletion")]]
char percentEncoded_toChar(std::string_view &str);
[[deprecated("Marked for deletion")]]
std::string char_toPercentEncoded(const char c);

}
}

#endif //BALEURI_INCLUDE_URIUTILS_H_
