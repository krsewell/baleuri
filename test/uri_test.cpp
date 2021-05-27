//
// Created by kris on 2021-05-24.
//

#include <gtest/gtest.h>
#include <Uri.h>

class UriFixture : public ::testing::Test {
 protected:
  bale::uri::Uri uri;
  void SetUp() override {
    uri.assign("");

  }
};