//
// Created by kris on 2021-05-21.
//

#ifndef BALEURI_INCLUDE_URI_H_
#define BALEURI_INCLUDE_URI_H_

#include <string>
#include <cctype>
#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace bale::uri {

class UriPath;

class Uri {
 protected:
  std::string uri;

  void convertRestricted();
  void lowercaseCharacters();
  void pctEncodedtoUpper();
  void pctEncodedUnreserved();
  void dotSegments();
  void emptyPath();
  void defaultPort();

 public:
  void assign(std::string);
  void clear();
  bool validate();
  void normalize();

  Uri *relative(UriPath &);
};

}

#endif //BALEURI_INCLUDE_URI_H_
