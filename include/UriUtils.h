//
// Created by kris on 2021-05-21.
//

#ifndef BALEURI_INCLUDE_URIUTILS_H_
#define BALEURI_INCLUDE_URIUTILS_H_

#include <string>
#include <string_view>
#include <stdexcept>

namespace bale {
namespace uri {

bool isUnreserved(const char c);

bool isGenDelimiter(const char c);

bool isSubDelimiter(const char c);

bool isReserved(const char c);

bool isHex(const char c);

short toShort(const char c);

char toChar(short value);

short hexPair_toShort(const char msd, const char lsd);

std::string short_toHexPair(const short in);

char percentEncoded_toChar(std::string_view &str);

std::string char_toPercentEncoded(const char c);

}
}

#endif //BALEURI_INCLUDE_URIUTILS_H_
