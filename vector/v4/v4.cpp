#include "v4.hpp"

constexpr v4f v4f::xyzw(f32 value) {
	return v4f(value, value, value, value);
}

v4f v4f::lerp(v4f a, v4f b, f32 f) {
	return v4f(f32_lerp(a.x, b.x, f), f32_lerp(a.y, b.y, f), f32_lerp(a.z, b.z, f), f32_lerp(a.w, b.w, f));
}

constexpr v4i v4i::xyzw(i32 value) {
	return v4i(value, value, value, value);
}