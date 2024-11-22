#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <pthread.h>

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
struct Thread;
template <typename T> struct ar;
template <typename T> struct gar;
struct v2f;
struct v2i;
struct v3f;
struct v3i;
struct v4f;
struct v4i;
struct m3f;
struct m4f;

#include "ctk.hpp"

#include "thread/thread.cpp"
#include "ar/ar.cpp"
#include "gar/gar.cpp"
#include "types/f32/f32.cpp"
#include "types/f64/f64.cpp"
#include "types/u8/u8.cpp"
#include "types/i8/i8.cpp"
#include "types/u16/u16.cpp"
#include "types/i16/i16.cpp"
#include "types/u32/u32.cpp"
#include "types/i32/i32.cpp"
#include "types/u64/u64.cpp"
#include "types/i64/i64.cpp"
#include "vector/v2/v2.cpp"
#include "vector/v3/v3.cpp"
#include "vector/v4/v4.cpp"
#include "matrix/m3/m3.cpp"
#include "matrix/m4/m4.cpp"

template <typename T> inline void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

template <typename T> inline T* alloc() {
	return (T*)std::malloc(sizeof(T));
}

template <typename T> inline T* alloc_copy(T value) {
	T* ptr = alloc<T>();
	*ptr = value;
	return ptr;
}

template <typename T> inline T* alloc_many(size_t count) {
	if (count == 0) {
		CTK_PANIC("alloc_many failed");
	}
	return (T*)std::malloc(sizeof(T) * count);
}

template <typename T> inline T* alloc_many_copy(const void* value, size_t count) {
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