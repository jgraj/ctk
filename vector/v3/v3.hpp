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

	v3f normalized() const;
	v3f negated() const;
	f32 sqr_len() const;
	f32 len() const;

	static constexpr v3f xyz(f32 value);
	static v3f scale(v3f a, f32 b);
	static v3f add(v3f a, v3f b);
	static v3f sub(v3f a, v3f b);
	static v3f mul(v3f a, v3f b);
	static v3f rand(v3f a, v3f b);
	static v3f lerp(v3f a, v3f b, f32 f);
	static v3f cross(v3f a, v3f b);
	static f32 dot(v3f a, v3f b);
	static f32 sqr_dst(v3f a, v3f b);
	static f32 dst(v3f a, v3f b);
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

	static constexpr v3i xyz(i32 value);
};