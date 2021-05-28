//
// Created by kris on 2021-05-21.
//

#include "UriUtils.h"

namespace bale::uri {

auto zero = [](auto &ctx) { _val(ctx) = 0; };
auto hex_a = [](auto &ctx) { _val(ctx) += _attr(ctx); };

x3::rule<class unreserved> const unreserved = "unreserved";
auto const unreserved_def = x3::alnum | x3::char_('-') | x3::char_('.') | x3::char_('_') | x3::char_('~');

x3::rule<class generaldelimiter> const generaldelimiter = "generaldelimiter";
auto const generaldelimiter_def = x3::char_(':') | x3::char_('/') | x3::char_('?') | x3::char_('#') |
    x3::char_('[') | x3::char_(']') | x3::char_('@');

x3::rule<class subdelimiter> const subdelimiter = "subdelimiter";
const auto subdelimiter_def = x3::char_('!') | x3::char_('$') | x3::char_('&') | x3::char_('\'') |
    x3::char_('(') | x3::char_(')') | x3::char_('*') | x3::char_('+') |
    x3::char_(',') | x3::char_(';') | x3::char_('=');

x3::rule<class reserved> const reserved = "reserved";
const auto reserved_def = generaldelimiter | subdelimiter;

x3::rule<class hex> const hex = "hex";
const auto hex_def = x3::digit | x3::char_('a', 'f') | x3::char_('A', 'F');

x3::rule<class percentencoded, int> percentencoded = "percentencoded";
const auto percentencoded_def = x3::char_('%')[zero] >> x3::hex[hex_a];

BOOST_SPIRIT_DEFINE(unreserved, generaldelimiter, subdelimiter, reserved, hex, percentencoded);

template<typename T>
bool parse(const std::string_view s, T x3parser) {
  auto start = s.begin();
  return x3::parse(start, s.end(), x3parser);
}

bool isUnreserved(const std::string_view s) {
  return parse(s, unreserved);
}

bool isGenDelimiter(const std::string_view s) {
  return parse(s, generaldelimiter);
}

bool isSubDelimiter(const std::string_view s) {
  return parse(s, subdelimiter);
}

bool isReserved(const std::string_view s) {
  return parse(s, reserved);
}

bool isHex(const std::string_view s) {
  return parse(s, hex);
}

bool percentDecoder(sv_iterator start, sv_iterator end, char &c) {
  auto b = x3::parse(start, end, percentencoded, c);
  return (b && start == end);
}

bool percentEncoder(sv_iterator chara, std::string_view &str) {
  return false;
}

short toShort(const char c) {
  switch (c) {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'A':
    case 'a': return 10;
    case 'B':
    case 'b': return 11;
    case 'C':
    case 'c': return 12;
    case 'D':
    case 'd': return 13;
    case 'E':
    case 'e': return 14;
    case 'F':
    case 'f': return 15;
    default:throw std::invalid_argument("passed a non-hex_ char to toShort");
  }
}

char toChar(short value) {
  switch (value) {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    case 10: return 'a';
    case 11: return 'b';
    case 12: return 'c';
    case 13: return 'd';
    case 14: return 'e';
    case 15: return 'f';
    default:throw std::invalid_argument("passed a non-hex_ short to toChar");
  }
}

short hexPair_toShort(const char msd, const char lsd) {
  auto m = toShort(msd) * 16;
  auto l = toShort(lsd);
  return m + l;
}

std::string short_toHexPair(const short in) {
  auto msd = toChar(in >> 4);
  auto lsd = toChar(in % 16);
  return std::string{msd, lsd, '\0'};
}

}