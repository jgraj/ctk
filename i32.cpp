inline i32 i32_min(i32 a, i32 b) {
	return a <= b ? a : b;
}

inline i32 i32_max(i32 a, i32 b) {
	return a >= b ? a : b;
}

inline i32 i32_abs(i32 a) {
	return a < 0 ? -a : a;
}

inline i32 i32_clamp(f32 a, f32 min, f32 max) {
	return i32_min(i32_max(a, min), max);
}

inline i32 i32_ceil(f32 value) {
	i32 int_part = (i32)value;
	if (value > int_part) {
		return int_part + 1;
	} else {
		return int_part;
	}
}

inline i32 i32_rand() {
	return ((i32)rand() << 16) | (i32)rand() - 2147483648;
}

inline i32 i32_rand_range(i32 min, i32 max) {
	return (i32_rand() % (max - min)) + min;
}