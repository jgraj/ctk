#include "v3.hpp"

v3f v3f::normalized() const {
	f32 len = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	if (len <= 0.0f) {
		return *this;
	}
	return v3f(this->x / len, this->y / len, this->z / len);
}

v3f v3f::negated() const {
	return v3f(-this->x, -this->y, -this->z);
}

f32 v3f::sqr_len() const {
	return this->x * this->x + this->y * this->y + this->z * this->z;
}

f32 v3f::len() const {
	return std::sqrt(this->sqr_len());
}

constexpr v3f v3f::xyz(f32 value) {
	return v3f(value, value, value);
}

v3f v3f::scale(v3f a, f32 b) {
	return v3f(a.x * b, a.y * b, a.z * b);
}

v3f v3f::add(v3f a, v3f b) {
	return v3f(a.x + b.x, a.y + b.y, a.z + b.z);
}

v3f v3f::sub(v3f a, v3f b) {
	return v3f(a.x - b.x, a.y - b.y, a.z - b.z);
}

v3f v3f::mul(v3f a, v3f b) {
	return v3f(a.x * b.x, a.y * b.y, a.z * b.z);
}

v3f v3f::rand(v3f a, v3f b) {
	return v3f(f32_rand(a.x, b.x), f32_rand(a.y, b.y), f32_rand(a.z, b.z));
}

v3f v3f::lerp(v3f a, v3f b, f32 f) {
	return v3f(f32_lerp(a.x, b.x, f), f32_lerp(a.y, b.y, f), f32_lerp(a.z, b.z, f));
}

v3f v3f::cross(v3f a, v3f b) {
	return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

f32 v3f::dot(v3f a, v3f b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 v3f::sqr_dst(v3f a, v3f b) {
	f32 x = a.x - b.x;
	f32 y = a.y - b.y;
	f32 z = a.z - b.z;
	return x * x + y * y + z * z;
}

f32 v3f::dst(v3f a, v3f b) {
	return std::sqrt(sqr_dst(a, b));
}

constexpr v3i v3i::xyz(i32 value) {
	return v3i(value, value, value);
}