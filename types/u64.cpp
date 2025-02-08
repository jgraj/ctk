u64 u64_parse(ar<char> str) {
	u64 value = 0;
	for (size_t a = 0; a < str.len; ++a) {
		char c = str[a];
		if (c < '0' || c > '9') {
			CTK_PANIC("u64_parse failed");
		}
		value = value * 10 + (c - '0');
	}
	return value;
}

inline u64 u64_min(u64 a, u64 b) {
	return a <= b ? a : b;
}

inline u64 u64_max(u64 a, u64 b) {
	return a >= b ? a : b;
}

inline u64 u64_rand() {
	return ((u64)u32_rand() << 32) | (u64)u32_rand();
}

inline u64 u64_rand_range(u64 min, u64 max) {
	return (u64_rand() % (max - min)) + min;
}