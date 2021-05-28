//
// Created by kris on 2021-05-26.
//

#ifndef BALEURI_INCLUDE_SCHEME_H_
#define BALEURI_INCLUDE_SCHEME_H_

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;

namespace bale::uri {

static const auto Scheme =
    x3::alpha >> *(x3::alpha | x3::digit | x3::char_('+') | x3::char_('-') | x3::char_('.'));

}

#endif //BALEURI_INCLUDE_SCHEME_H_
