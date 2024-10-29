u64 u64_parse(ar<char> str) {
	u64 value = 0;
	for (size_t i = 0; i < str.len; ++i) {
		char c = str[i];
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