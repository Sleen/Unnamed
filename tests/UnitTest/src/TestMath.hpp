#pragma once

#include "UnitTest.hpp"
#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"
#include "Math/Rect.hpp"


using namespace me;

BEGIN_TESTS(Math)

TEST(Vector) {
	CHECK(Vector2(1, 1) + Vector2(1, 1) == Vector2(2, 2));
	CHECK(Vector2(1, 1) - Vector2(1, 1) == Vector2(0, 0));
	CHECK(Vector2(1, 1) * Vector2(1, 1) == 2);
	CHECK(Vector2(1, 1) * 2 == Vector2(2, 2));
	CHECK(Vector2(1, 1) / 2 == Vector2(0.5, 0.5));
	CHECK(Vector2(1, 1).Length2() == 2);
	CHECK(Vector2(0, 0).IsZero());
	CHECK(Vector2(10, 0).Normalize() == 10);
}

TEST(Rect) {

}

TEST(Matrix) {
	Matrix4 m = Matrix4::Identity();
	CHECK(m*m == m);
}

END_TESTS()
