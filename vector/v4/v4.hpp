struct v4f {
	union {
		struct {
			f32 x;
			f32 y;
			f32 z;
			f32 w;
		};
		f32 data[4];
	};

	constexpr v4f() = default;
	constexpr v4f(f32 _x, f32 _y, f32 _z, f32 _w): x(_x), y(_y), z(_z), w(_w) {}

	static constexpr v4f xyzw(f32 value);
	static v4f lerp(v4f a, v4f b, f32 f);
};

struct v4i {
	union {
		struct {
			i32 x;
			i32 y;
			i32 z;
			i32 w;
		};
		i32 data[4];
	};

	constexpr v4i() = default;
	constexpr v4i(i32 _x, i32 _y, i32 _z, i32 _w): x(_x), y(_y), z(_z), w(_w) {}
	
	static constexpr v4i xyzw(i32 value);
};