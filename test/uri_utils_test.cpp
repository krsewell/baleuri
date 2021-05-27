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

TEST(UriUtil, is_unreserved_non_ascii) {
  ASSERT_FALSE(bale::uri::isUnreserved((char) 0xff));
}

TEST(UriUtil, is_general_delimiter_non_ascii) {
  ASSERT_FALSE(bale::uri::isGenDelimiter((char) 0xff));
}

TEST(UriUtil, is_general_delimiter_negative) {
  ASSERT_FALSE(bale::uri::isGenDelimiter('a'));
}

TEST(UriUtil, is_general_delimiter_all) {
  char test[] = {':', '/', '?', '#', '[', ']', '@'};
  for (int i = 0, size = sizeof test; i < size; i++) {
    EXPECT_TRUE(bale::uri::isGenDelimiter(test[i]));
  }
}

TEST(UriUtil, is_sub_delimiter_non_ascii) {
  ASSERT_FALSE(bale::uri::isSubDelimiter((char) 0xff));
}

TEST(UriUtil, is_sub_delimiter_negative) {
  ASSERT_FALSE(bale::uri::isSubDelimiter('a'));
}

TEST(UriUtil, is_sub_delimiter_all) {
  char test[] = {'!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '='};
  for (int i = 0, size = sizeof test; i < size; i++) {
    EXPECT_TRUE(bale::uri::isSubDelimiter(test[i]));
  }
}

TEST(UriUtil, is_reserved_all) {
  char test[] = {':', '/', '?', '#', '[', ']', '@', '!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '='};
  for (int i = 0, size = sizeof test; i < size; i++) {
    EXPECT_TRUE(bale::uri::isReserved(test[i]));
  }
}

TEST(SingleCharTransform, is_hex_all) {
  char test[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  for (int i = 0, size = sizeof test; i < size; i++) {
    EXPECT_TRUE(bale::uri::isHex(test[i]));
  }
}

TEST(SingleCharTransform, is_hex_caps) {
  char test[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  for (int i = 0, size = sizeof test; i < size; i++) {
    EXPECT_TRUE(bale::uri::isHex(test[i]));
  }
}

TEST(SingleCharTransform, is_hex_negative) {
  ASSERT_FALSE(bale::uri::isHex('g'));
}

TEST(SingleCharTransform, to_short_null) {
  try {
    bale::uri::toShort('\0');
    FAIL() << "Expected Invalid Argument";
  } catch (std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex char to toShort"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_short_arith) {
  ASSERT_EQ(bale::uri::toShort('A'), 10);
}

TEST(SingleCharTransform, to_short_a) {
  ASSERT_EQ(bale::uri::toShort('a'), 10);
}

TEST(SingleCharTransform, to_short_Z) {
  try {
    bale::uri::toShort('Z');
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex char to toShort"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_char_oob) {
  try {
    bale::uri::toChar(16);
    FAIL() << "Expected ";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex short to toChar"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_char_oob2) {
  try {
    bale::uri::toChar(-1);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex short to toChar"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_char_zero) {
  auto uut = bale::uri::toChar(0);
  EXPECT_EQ(uut, '0');
}

TEST(HexPair, hexpair_to_short) {
  std::vector<std::string> inputs{"00", "01", "ab", "ff", "f0", "0f"};
  std::vector<short> expected{15, 240, 255, 171, 1, 0};
  for (const auto & item : inputs) {
    auto uut = bale::uri::hexPair_toShort(item[0], item[1]);
    EXPECT_EQ((int)uut, (int)expected.back());
    expected.pop_back();
  }
}

TEST(HexPair, short_to_hexpair) {
  std::vector<short> inputs{0, 1, 171, 255, 240, 15};
  std::vector<std::string> expected{"0f", "f0", "ff", "ab", "01", "00"};
  for (const auto & item : inputs) {
    auto uut = bale::uri::short_toHexPair(item);
    EXPECT_STREQ(uut.c_str(), expected.back().c_str());
    expected.pop_back();
  }
}


