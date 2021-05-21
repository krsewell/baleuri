//
// Created by kris on 2021-05-21.
//

#ifndef BALEURI_INCLUDE_URIBUILDER_H_
#define BALEURI_INCLUDE_URIBUILDER_H_

class UriBuilder {
 public:
  UriBuilder();
  void scheme(char*);
  void userinfo(char*);
  void host(char*);
  void port(int);
  void path(char*);
  void query(char*);
  void fragment(char*);
  Uri* build();
};


#endif //BALEURI_INCLUDE_URIBUILDER_H_
