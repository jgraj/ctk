inline f64 f64_min(f64 a, f64 b) {
	return a <= b ? a : b;
}

inline f64 f64_max(f64 a, f64 b) {
	return a >= b ? a : b;
}

inline f64 f64_clamp(f64 a, f64 min, f64 max) {
	return f64_min(f64_max(a, min), max);
}