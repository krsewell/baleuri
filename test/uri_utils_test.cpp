//
// Created by kris on 2021-05-21.
//

#include "../include/UriUtils.h"
#include <gtest/gtest.h>

const std::vector<std::string> ur{"a", "z", "A", "Z", "0", "9", "-", ".", "_", "~"};
const std::vector<std::string> gd{":", "/", "?", "#", "[", "]", "@"};
const std::vector<std::string> sd{"!", "$", "&", "'", "(", ")", "*", "+", ",", ";", "="};
const std::vector<std::string> h{"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                                 "a", "b", "c", "d", "e", "f",
                                 "A", "B", "C", "D", "E", "F"};

TEST(Char, isUnreservedPositive) {
  const std::vector<std::string> &items = ur;
  for (const auto &item : items) {
    EXPECT_TRUE(bale::uri::isUnreserved(item));
  }
}

TEST(Char, isUnreservedNegative) {
  const std::vector<std::string> &items = gd;
  for (const auto &item : items) {
    EXPECT_FALSE(bale::uri::isUnreserved(item));
  }
}

TEST(Char, isGenDelimiterPositive) {
  const std::vector<std::string> &items = gd;
  for (const auto &item : items) {
    EXPECT_TRUE(bale::uri::isGenDelimiter(item));
  }
}

TEST(Char, isGenDelimiterNegative) {
  const std::vector<std::string> &items = sd;
  for (const auto &item : items) {
    EXPECT_FALSE(bale::uri::isGenDelimiter(item));
  }
}

TEST(Char, isSubDelimiterPositive) {
  const std::vector<std::string> &items = sd;
  for (const auto &item : items) {
    EXPECT_TRUE(bale::uri::isSubDelimiter(item));
  }
}

TEST(Char, isSubDelimiterNegative) {
  const std::vector<std::string> &items = gd;
  for (const auto &item : items) {
    EXPECT_FALSE(bale::uri::isSubDelimiter(item));
  }
}

TEST(Char, isReservedPositive) {
  std::vector<std::string> items;
  items.reserve(gd.size() + sd.size());
  items.insert(items.end(), gd.begin(), gd.end());
  items.insert(items.end(), sd.begin(), sd.end());
  for (const auto &item : items) {
    EXPECT_TRUE(bale::uri::isReserved(item));
  }
}

TEST(Char, isReservedNegative) {
  const std::vector<std::string> &items = ur;
  for (const auto &item : items) {
    EXPECT_FALSE(bale::uri::isGenDelimiter(item));
    EXPECT_FALSE(bale::uri::isSubDelimiter(item));
    EXPECT_FALSE(bale::uri::isReserved(item));
  }
}

TEST(Char, isHexPositive) {
  const std::vector<std::string> &items = h;
  for (const auto &item : items) {
    EXPECT_TRUE(bale::uri::isHex(item));
  }
}

TEST(Char, isHexNegative) {
  const std::vector<std::string> &items = gd;
  for (const auto &item : items) {
    EXPECT_FALSE(bale::uri::isHex(item));
  }
}

TEST(SingleCharTransform, to_short_null) {
  try {
    bale::uri::toShort('\0');
    FAIL() << "Expected Invalid Argument";
  } catch (std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex_ char to toShort"));
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
    EXPECT_EQ(err.what(), std::string("passed a non-hex_ char to toShort"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_char_oob) {
  try {
    bale::uri::toChar(16);
    FAIL() << "Expected ";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex_ short to toChar"));
  } catch (...) {
    FAIL() << "Wrong exception type thrown";
  }
}

TEST(SingleCharTransform, to_char_oob2) {
  try {
    bale::uri::toChar(-1);
    FAIL() << "Expected std::invalid_argument";
  } catch (const std::invalid_argument &err) {
    EXPECT_EQ(err.what(), std::string("passed a non-hex_ short to toChar"));
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
  for (const auto &item : inputs) {
    auto uut = bale::uri::short_toHexPair(item);
    EXPECT_STREQ(uut.c_str(), expected.back().c_str());
    expected.pop_back();
  }
}

TEST(PercentEncoding, PercentDecoderPositive) {
  std::vector<std::pair<std::string, char>> items{
      std::pair("%30", '0'), std::pair("%34", '4'), std::pair("%40", '@'), std::pair("%3e", '>'),
      std::pair("%3E", '>'), std::pair("%20", ' '), std::pair("%25", '%'), std::pair("%0A", '\n')};
  for (const auto &item : items) {
    char c;
    auto it = item.first.cbegin();
    if (bale::uri::percentDecoder(it, item.first.end(), c)) {
      EXPECT_EQ(c, item.second);
    }
  }
}