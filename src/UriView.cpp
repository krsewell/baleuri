//
// Created by kris on 2021-05-18.
//

#include "../include/UriView.h"

void to_uri(const char *in, Uri &out) {
  auto in_size = std::strnlen_s(in, sizeof out.bytes);
  if (in_size == 0 || in_size == sizeof out.bytes) {
    std::printf("string '%s' is too large for this Uri type with size %zu", in, sizeof out.bytes);
    return
  }
  std::strncpy(out.bytes, in, insize);
  out.pointers[0] = (char *) out.bytes + std::strchr(out.bytes, ':');
  out.pointers[1] = (char *) out.bytes + std::strchr(out.bytes, '/');
  out.pointers[2] = (char *) out.bytes + std::strchr(out.bytes, '?');
  out.pointers[3] = (char *) out.bytes + std::strchr(out.bytes, '#');

}


std::string_view scheme(const Uri& uri) {
  /*
   * Everything from bytes[0] up to ':', noninclusive is considered scheme. Scheme names consist of a sequence of chara-
   * cters beginning with a letter and followed by any combination of letters, digits, plus ("+"), period ("."), or
   * hyphen ("-"). URI scheme specifications must define their own syntax so that all strings matching their scheme-
   * specific syntax will also match the <absolute-URI> grammar.
   */
  auto size = uri.pointers[0] - uri.bytes;
  return std::isalpha(uri.bytes[0]) ? std::string_view(uri.bytes, size) : std::string_view();
}

std::string_view authority(const Uri& uri) {
  /*
   * The authority component is preceded by a double slash ("//") and is
   * terminated by the next slash ("/"), question mark ("?"), or number
   * sign ("#") character, or by the end of the URI. URI producers and
   * normalizers should omit the ":" delimiter that separates host from
   * port if the port component is empty.
   *
   * If a URI contains an authority component, then the path component
   * must either be empty or begin with a slash ("/") character.  Non-
   * validating parsers (those that merely separate a URI reference into
   * its major components) will often ignore the subcomponent structure of
   * authority, treating it as an opaque string from the double-slash to
   * the first terminating delimiter, until such time as the URI is
   * dereferenced.
   */
  if (*(uri.pointers[1]) == *(uri.pointers[1] + 1) && *(uri.pointers[1]) == '/') {
    char comp[3] = {'/', '?', '#'};
  }
}

std::string_view path(const Uri&);
std::string_view query(const Uri&);
std::string_view fragment(const Uri&);