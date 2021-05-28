//
// Created by kris on 2021-05-26.
//

#include <Uri.h>

namespace bale::uri {

void Uri::assign(std::string s) {
  uri.assign(s);
}

void Uri::clear() {
  uri.clear();
}

bool Uri::validate() {
  return false;
}

void Uri::normalize() {
  lowercaseCharacters();
  convertRestricted();
}

Uri *Uri::relative(UriPath &) {
  return nullptr;
}

void Uri::convertRestricted() {}
void Uri::lowercaseCharacters() {}
void Uri::pctEncodedtoUpper() {}
void Uri::pctEncodedUnreserved() {}
void Uri::dotSegments() {}
void Uri::emptyPath() {}
void Uri::defaultPort() {}

}

