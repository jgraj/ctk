inline i64 i64_min(i64 a, i64 b) {
	return a <= b ? a : b;
}

inline i64 i64_max(i64 a, i64 b) {
	return a >= b ? a : b;
}

inline i64 i64_rand() {
	return ((i64)i32_rand() << 32) | (i64)i32_rand();
}

inline i64 i64_rand_range(i64 min, i64 max) {
	return (i64_rand() % (max - min)) + min;
}