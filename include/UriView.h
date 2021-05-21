//
// Created by kris on 2021-05-18.
//

#ifndef _URIVIEW_H_
#define _URIVIEW_H_

#include <string>
#include <math.h>
#include <ctype.h>

struct Uri {
  std::string_view *pointers[8]; // 1 cache line
  char bytes[256] = {0}; // 4 cache lines
};

void to_uri(const char *, Uri &);
std::string_view &scheme(const Uri &);
std::string_view &authority(const Uri &);
std::string_view &path(const Uri &);
std::string_view &query(const Uri &);
std::string_view &fragment(const Uri &);

#endif //_URIVIEW_H_
