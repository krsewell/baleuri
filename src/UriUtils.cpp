//
// Created by kris on 2021-05-21.
//

#include "../include/UriUtils.h"

namespace bale::uri {
bool isUnreserved(const char c) {
  return std::isalnum(c) || c == '-' || c == '.' || c == '_' || c == '~';
}

bool isGenDelimiter(const char c) {
  return c == ':' || c == '/' || c == '?' || c == '#' || c == '[' || c == ']' || c == '@';
}

bool isSubDelimiter(const char c) {
  return c == '!' || c == '$' || c == '&' || c == '\'' || c == '(' || c == ')' || c == '*' ||
      c == '+' || c == ',' || c == ';' || c == '=';
}

bool isReserved(const char c) {
  return isGenDelimiter(c) || isSubDelimiter(c);
}

bool isHex(const char c) {
  return (std::isdigit(c) || c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f'
      || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F');
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
    default:throw std::invalid_argument("passed a non-hex char to toShort");
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
    default:throw std::invalid_argument("passed a non-hex short to toChar");
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

char percentEncoded_toChar(std::string_view &str) {
  if (str.size() < 3 || str[0] != '%' || !isHex(str[1]) || !isHex(str[2])) {
    throw std::invalid_argument("passed an invalid percent encoded string");
  }
  auto value = hexPair_toShort(str[1], str[2]);
  return (char) value;
}

std::string char_toPercentEncoded(const char c) {
  auto value = short_toHexPair((short) c);
  return std::string{'%', (char) value[0], (char) value[1]};
}
}