#include "v2.hpp"

constexpr v2f v2f::xy(f32 value) {
	return v2f(value, value);
}

v2f v2f::mul(v2f a, v2f b) {
	return v2f(a.x * b.x, a.y * b.y);
}

constexpr v2f v2i::to_v2f() const {
	return v2f(this->x, this->y);
}

constexpr v2i v2i::xy(i32 value) {
	return v2i(value, value);
}

i32 v2i::sqr_dst(v2i a, v2i b) {
	i32 x = a.x - b.x;
	i32 y = a.y - b.y;
	return x * x + y * y;
}

i32 v2i::dst(v2i a, v2i b) {
	return std::sqrt(sqr_dst(a, b));
}

v2i v2i::add(v2i a, v2i b) {
	return v2i(a.x + b.x, a.y + b.y);
}