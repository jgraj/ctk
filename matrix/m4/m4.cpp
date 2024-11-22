#include "m4.hpp"

constexpr m4f::m4f(f32 _00, f32 _01, f32 _02, f32 _03, f32 _10, f32 _11, f32 _12, f32 _13, f32 _20, f32 _21, f32 _22, f32 _23, f32 _30, f32 _31, f32 _32, f32 _33) {
	this->data[0]  = _00; this->data[1]  = _01; this->data[2]  = _02; this->data[3]  = _03;
	this->data[4]  = _10; this->data[5]  = _11; this->data[6]  = _12; this->data[7]  = _13;
	this->data[8]  = _20; this->data[9]  = _21; this->data[10] = _22; this->data[11] = _23;
	this->data[12] = _30; this->data[13] = _31; this->data[14] = _32; this->data[15] = _33;
}

constexpr f32& m4f::operator[] (size_t index) {
	return data[index];
}

constexpr const f32& m4f::operator[] (size_t index) const {
	return data[index];
}

m4f m4f::transposed() const {
	return m4f(
		this->data[0], this->data[4], this->data[8],  this->data[12],
		this->data[1], this->data[5], this->data[9],  this->data[13],
		this->data[2], this->data[6], this->data[10], this->data[14],
		this->data[3], this->data[7], this->data[11], this->data[15]
	);
}

m4f m4f::mul(m4f a, m4f b) {
	return m4f(
		a[0]  * b[0] + a[1]  * b[4] + a[2]  * b[8]  + a[3]  * b[12],
		a[0]  * b[1] + a[1]  * b[5] + a[2]  * b[9]  + a[3]  * b[13],
		a[0]  * b[2] + a[1]  * b[6] + a[2]  * b[10] + a[3]  * b[14],
		a[0]  * b[3] + a[1]  * b[7] + a[2]  * b[11] + a[3]  * b[15],
		a[4]  * b[0] + a[5]  * b[4] + a[6]  * b[8]  + a[7]  * b[12],
		a[4]  * b[1] + a[5]  * b[5] + a[6]  * b[9]  + a[7]  * b[13],
		a[4]  * b[2] + a[5]  * b[6] + a[6]  * b[10] + a[7]  * b[14],
		a[4]  * b[3] + a[5]  * b[7] + a[6]  * b[11] + a[7]  * b[15],
		a[8]  * b[0] + a[9]  * b[4] + a[10] * b[8]  + a[11] * b[12],
		a[8]  * b[1] + a[9]  * b[5] + a[10] * b[9]  + a[11] * b[13],
		a[8]  * b[2] + a[9]  * b[6] + a[10] * b[10] + a[11] * b[14],
		a[8]  * b[3] + a[9]  * b[7] + a[10] * b[11] + a[11] * b[15],
		a[12] * b[0] + a[13] * b[4] + a[14] * b[8]  + a[15] * b[12],
		a[12] * b[1] + a[13] * b[5] + a[14] * b[9]  + a[15] * b[13],
		a[12] * b[2] + a[13] * b[6] + a[14] * b[10] + a[15] * b[14],
		a[12] * b[3] + a[13] * b[7] + a[14] * b[11] + a[15] * b[15]
	);
}

constexpr m4f m4f::ident() {
	return m4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}