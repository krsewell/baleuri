//
// Created by kris on 2021-05-21.
//

#include "../include/UriUtils.h"
#include <gtest/gtest.h>

TEST(UriUtil, is_unreserved_positive) {
ASSERT_TRUE(bale::uri::isUnreserved('a'));
}

TEST(UriUtil, is_unreserved_negative) {
ASSERT_FALSE(bale::uri::isUnreserved(':'));
}

TEST(UriUtil, is_unreserved_special) {
ASSERT_FALSE(bale::uri::isUnreserved((char)0x20));
}