#ifndef CTK_PANIC
#define CTK_PANIC(...) std::printf(__VA_ARGS__); std::exit(1);
#endif

typedef float f32;
typedef double f64;
typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;

#include "gar.cpp"
#include "f32.cpp"
#include "f64.cpp"
#include "u8.cpp"
#include "i8.cpp"
#include "u16.cpp"
#include "i16.cpp"
#include "u32.cpp"
#include "i32.cpp"
#include "u64.cpp"
#include "i64.cpp"

constexpr f64 pi = 3.14159265358979323846;
constexpr f64 deg2rad = pi / 180.0;
constexpr f64 rad2deg = 180.0 / pi;

#include "v2.cpp"
#include "v3.cpp"
#include "v4.cpp"
#include "m3.cpp"
#include "m4.cpp"

template <typename T>
inline void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

template <typename T>
inline T* alloc() {
	return (T*)std::malloc(sizeof(T));
}

template <typename T>
inline T* alloc_copy(T value) {
	T* ptr = alloc<T>();
	*ptr = value;
	return ptr;
}

template <typename T>
inline T* alloc_many(size_t count) {
	if (count == 0) {
		CTK_PANIC("alloc_many failed");
	}
	return (T*)std::malloc(sizeof(T) * count);
}

template <typename T>
inline T* alloc_many_copy(const void* value, size_t count) {
	if (count == 0) {
		CTK_PANIC("alloc_many failed");
	}
	T* ptr = (T*)std::malloc(sizeof(T) * count);
	std::memcpy(ptr, value, sizeof(T) * count);
	return ptr;
}

ar<char> alloc_format(const char* format, ...) {
	va_list args;
	va_start(args, format);
	char* string;
	int len = vasprintf(&string, format, args);
	if (len == -1) {
		CTK_PANIC("vasprintf failed");
	}
	va_end(args);
	return ar<char>(string, len);
}