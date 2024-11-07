inline u8 u8_rand() {
	return (u8)(rand() % 256);
}

inline u8 u8_rand_range(u8 min, u8 max) {
	return (u8_rand() % (max - min)) + min;
}