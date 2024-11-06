inline u32 u32_rand() {
	return ((u32)rand() << 16) | (u32)rand();
}

inline u32 u32_rand_range(u32 min, u32 max) {
	return (u32_rand() % (max - min)) + min;
}