#include "m3.hpp"

constexpr m3f::m3f(f32 _00, f32 _01, f32 _02, f32 _10, f32 _11, f32 _12, f32 _20, f32 _21, f32 _22) {
	this->data[0] = _00; this->data[1] = _01; this->data[2] = _02;
	this->data[3] = _10; this->data[4] = _11; this->data[5] = _12;
	this->data[6] = _20; this->data[7] = _21; this->data[8] = _22;
}

constexpr f32& m3f::operator[] (size_t index) {
	return data[index];
}

constexpr const f32& m3f::operator[] (size_t index) const {
	return data[index];
}

m3f m3f::transposed() const {
	return m3f(
		this->data[0], this->data[3], this->data[6],
		this->data[1], this->data[4], this->data[7],
		this->data[2], this->data[5], this->data[8]
	);
}

constexpr m3f m3f::ident() {
	return m3f(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	);
}