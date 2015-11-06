#pragma once

#include "UnitTest.hpp"
#include "Render/Color.hpp"


using namespace me;

BEGIN_TESTS(Color)

TEST(FromName) {
	CHECK(Color::FromName("red") == Color::Red);
	CHECK(Color::FromName("RED") == Color::Red);
	CHECK(Color::FromName("RED") == Color::Red);
	CHECK(Color::FromName("#f00") == Color::Red);
	CHECK(Color::FromName("#FF00") == Color::Red);
	CHECK(Color::FromName("#FF0000") == Color::Red);
	CHECK_THROW(Color::FromName("red1"), FormatException);
	CHECK_THROW(Color::FromName("#red"), FormatException);
	CHECK_THROW(Color::FromName("#g00"), FormatException);
}

END_TESTS()
