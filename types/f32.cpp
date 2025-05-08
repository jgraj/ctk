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

inline bool f32_cmp(f32 a, f32 b, f32 epsilon) {
	return std::fabs(a - b) < epsilon;
}

inline f32 f32_lerp(f32 a, f32 b, f64 t, f64 dt) {
	f64 ht = -t / std::log2(0.001);
	return b + (a - b) * std::exp2(-dt / ht);
}

// inline f32 f32_smoothstep(f32 a, f32 b, f64 f) {
// 	f = f64_clamp(f, 0.0, 1.0);
// 	return f32_lerp(a, b, f * f * (3.0 - 2.0 * f));
// }

inline f32 f32_rand_01() {
	return (f32)(rand()) / (f32)(RAND_MAX);
}

inline f32 f32_rand(f32 min, f32 max) {
	return f32_rand_01() * (max - min) + min;
}