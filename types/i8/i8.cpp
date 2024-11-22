inline i8 i8_rand() {
	return (i8)((rand() % 256) - 128);
}

inline i8 i8_rand_range(i8 min, i8 max) {
	return (i8_rand() % (max - min)) + min;
}