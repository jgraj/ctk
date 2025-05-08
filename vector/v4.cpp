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
	static v4f lerp(v4f a, v4f b, f64 t, f64 dt);
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

constexpr v4f v4f::xyzw(f32 value) {
	return v4f(value, value, value, value);
}

v4f v4f::lerp(v4f a, v4f b, f64 t, f64 dt) {
	return v4f(f32_lerp(a.x, b.x, t, dt), f32_lerp(a.y, b.y, t, dt), f32_lerp(a.z, b.z, t, dt), f32_lerp(a.w, b.w, t, dt));
}

constexpr v4i v4i::xyzw(i32 value) {
	return v4i(value, value, value, value);
}