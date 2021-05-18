/*
 * URI_test.cpp
 *
 *  Created on: May 17, 2021
 *      Author: kris
 */

#include <gtest/gtest.h>
#include "../include/UniformResourceIdentifier.h"

TEST(BaseUri, BasicUri) {
  auto uut = URI("ftp://www.google.com");
  EXPECT_STREQ(uut.scheme(),"ftp");
  EXPECT_STREQ(uut.host(),"www.google.com");
  EXPECT_STREQ(uut.path(),"");
};

TEST(BaseUri, PathUri){
  auto uut = URI("http://www.google.com/search/theresult.py?query=pizza&beer");
  EXPECT_STREQ(uut.path(),"/search/theresult.py");
  EXPECT_STREQ(uut.query(), "?query=pizza&beer");
};

TEST(BaseUri, FragUri){
  auto uut = URI("https://myspace.me/myprofile/page.php#myAnger");
  EXPECT_STREQ(uut.scheme(),"https");
  EXPECT_STREQ(uut.host(),"myspace.me");
  EXPECT_STREQ(uut.path(),"/myprofile/page.php");
  EXPECT_STREQ(uut.fragment(),"myanger");
}

TEST(BaseUri, NonAuthority){
  auto uut = URI("urn:649e69a9-6d38-4e6a-afee-374780bc5b5a");
  EXPECT_STREQ(uut.scheme(),"urn");
  EXPECT_STREQ(uut.path(),"649e69a9-6d38-4e6a-afee-374780bc5b5a");
}

TEST(BaseUri, Authority){
  auto uut = URI("ssh://user;fingerprint=ssh-dss-c1-c1-c1-c1@github.com:5678");
  EXPECT_STREQ(uut.userinfo(),"user;fingerprint=ssh-dss-c1-c1-c1-c1");
  EXPECT_STREQ(uut.host(),"github.com");
  EXPECT_STREQ(uut.port(),"5678");
}