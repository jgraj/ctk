inline i16 i16_rand() {
	return (i16)((rand() % 65536) - 32768);
}

inline i16 i16_rand_range(i16 min, i16 max) {
	return (i16_rand() % (max - min)) + min;
}