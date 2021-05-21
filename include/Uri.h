//
// Created by kris on 2021-05-21.
//

#ifndef BALEURI_INCLUDE_URI_H_
#define BALEURI_INCLUDE_URI_H_

class Uri {
 public:
  Uri();
  bool validate();
  Uri* relative(UriPath&);
};

#endif //BALEURI_INCLUDE_URI_H_
