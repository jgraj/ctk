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

	static constexpr v2f xy(f32 value);
	static v2f mul(v2f a, v2f b);
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
};