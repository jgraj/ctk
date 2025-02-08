inline f32 f32_min(f32 a, f32 b) {
	return a <= b ? a : b;
}

inline f32 f32_max(f32 a, f32 b) {
	return a >= b ? a : b;
}

inline i32 f32_round(f32 a) {
	return a >= 0.0f ? (i32)(a + 0.5f) : (i32)(a - 0.5f);
}

inline f32 f32_clamp(f32 a, f32 min, f32 max) {
	return f32_min(f32_max(a, min), max);
}

inline f32 f32_abs(f32 a) {
	return a < 0.0f ? -a : a;
}

inline f32 f32_lerp(f32 a, f32 b, f32 f) {
	f = f32_clamp(f, 0.0f, 1.0f);
	return a * (1.0f - f) + (b * f);
}

inline f32 f32_smoothstep(f32 a, f32 b, f32 f) {
	f = f32_clamp(f, 0.0f, 1.0f);
	return f32_lerp(a, b, f * f * (3.0f - 2.0f * f));
}

inline f32 f32_rand_01() {
	return (f32)(rand()) / (f32)(RAND_MAX);
}

inline f32 f32_rand(f32 min, f32 max) {
	return f32_rand_01() * (max - min) + min;
}