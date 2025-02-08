struct v2f {
	union {
		struct {
			f32 x;
			f32 y;
		};
		f32 data[2];
	};

	constexpr v2f() = default;
	constexpr v2f(f32 _x, f32 _y): x(_x), y(_y) {}

	constexpr v2i to_v2i() const;
	v2f rounded() const;

	static constexpr v2f xy(f32 value);
	static v2f add(v2f a, v2f b);
	static v2f sub(v2f a, v2f b);
	static v2f mul(v2f a, v2f b);
	static v2f mul_f32(v2f a, f32 b);
	static v2f div(v2f a, v2f b);
	static v2f div_f32(v2f a, f32 b);
};

struct v2i {
	union {
		struct {
			i32 x;
			i32 y;
		};
		i32 data[2];
	};

	constexpr v2i() = default;
	constexpr v2i(i32 _x, i32 _y): x(_x), y(_y) {}

	constexpr v2f to_v2f() const;
	
	static constexpr v2i xy(i32 value);
	static i32 sqr_dst(v2i a, v2i b);
	static i32 dst(v2i a, v2i b);
	static v2i add(v2i a, v2i b);
	static v2i sub(v2i a, v2i b);
	static v2i mul(v2i a, v2i b);
	static v2i div(v2i a, v2i b);
};

constexpr v2f v2f::xy(f32 value) {
	return v2f(value, value);
}

constexpr v2i v2f::to_v2i() const {
	return v2i((i32)this->x, (i32)this->y);
}

v2f v2f::rounded() const {
	return v2f((i32)this->x, (i32)this->y);
}

v2f v2f::add(v2f a, v2f b) {
	return v2f(a.x + b.x, a.y + b.y);
}

v2f v2f::sub(v2f a, v2f b) {
	return v2f(a.x - b.x, a.y - b.y);
}

v2f v2f::mul(v2f a, v2f b) {
	return v2f(a.x * b.x, a.y * b.y);
}

v2f v2f::mul_f32(v2f a, f32 b) {
	return v2f(a.x * b, a.y * b);
}

v2f v2f::div(v2f a, v2f b) {
	return v2f(a.x / b.x, a.y / b.y);
}

v2f v2f::div_f32(v2f a, f32 b) {
	return v2f(a.x / b, a.y / b);
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

v2i v2i::sub(v2i a, v2i b) {
	return v2i(a.x - b.x, a.y - b.y);
}

v2i v2i::mul(v2i a, v2i b) {
	return v2i(a.x * b.x, a.y * b.y);
}

v2i v2i::div(v2i a, v2i b) {
	return v2i(a.x / b.x, a.y / b.y);
}