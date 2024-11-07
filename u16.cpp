inline u16 u16_rand() {
	return (u16)(rand() % 65536);
}

inline u16 u16_rand_range(u16 min, u16 max) {
	return (u16_rand() % (max - min)) + min;
}