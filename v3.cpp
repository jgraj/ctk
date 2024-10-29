struct v3f {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
		};
		f32 data[3];
	};

	constexpr v3f() = default;

	constexpr v3f(f32 _x, f32 _y, f32 _z): x(_x), y(_y), z(_z) {}

	static constexpr v3f xyz(f32 value) {
		return v3f(value, value, value);
	}

	v3f normalized() const {
		f32 len = std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
		if (len <= 0.0f) {
			return *this;
		}
		return v3f(this->x / len, this->y / len, this->z / len);
	}

	v3f negated() const {
		return v3f(-this->x, -this->y, -this->z);
	}

	f32 sqr_len() const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	f32 len() const {
		return std::sqrt(this->sqr_len());
	}

	static v3f scale(v3f a, f32 b) {
		return v3f(a.x * b, a.y * b, a.z * b);
	}

	static v3f add(v3f a, v3f b) {
		return v3f(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	static v3f sub(v3f a, v3f b) {
		return v3f(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	static v3f mul(v3f a, v3f b) {
		return v3f(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	static v3f rand(v3f a, v3f b) {
		return v3f(f32_rand(a.x, b.x), f32_rand(a.y, b.y), f32_rand(a.z, b.z));
	}

	static v3f lerp(v3f a, v3f b, f32 f) {
		return v3f(f32_lerp(a.x, b.x, f), f32_lerp(a.y, b.y, f), f32_lerp(a.z, b.z, f));
	}

	static v3f cross(v3f a, v3f b) {
		return v3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
	}

	static f32 dot(v3f a, v3f b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	static f32 sqr_dst(v3f a, v3f b) {
		f32 x = a.x - b.x;
		f32 y = a.y - b.y;
		f32 z = a.z - b.z;
		return x * x + y * y + z * z;
	}

	static f32 dst(v3f a, v3f b) {
		return std::sqrt(sqr_dst(a, b));
	}
};

struct v3i {
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	};

	constexpr v3i() = default;

	constexpr v3i(i32 _x, i32 _y, i32 _z): x(_x), y(_y), z(_z) {}

	static constexpr v3i xyz(i32 value) {
		return v3i(value, value, value);
	}
};