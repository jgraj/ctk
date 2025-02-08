#define _GNU_SOURCE 1
#include <cstdlib>
#include <cstdarg>
#include <cstdint>
#include <cstddef>
#include <cstdio>
#include <cmath>
#include <cstring>

#ifdef _WIN32
#define CTK_WIN
#define WINVER _WIN32_WINNT_WIN10
#include <windows.h>
#endif

#ifdef __linux__
#define CTK_LIN
#include <pthread.h>
#endif

#ifndef CTK_PANIC
#define CTK_PANIC(...) std::printf(__VA_ARGS__); std::exit(1);
#endif

#define AR_STR(str) (ar<u8>(((u8*)str), sizeof(str) - 1))

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

constexpr f64 pi = 3.14159265358979323846;
constexpr f64 deg2rad = pi / 180.0;
constexpr f64 rad2deg = 180.0 / pi;

template <typename T> inline void swap(T* a, T* b);
template <typename T> inline T* alloc(T value);
template <typename T> inline T* alloc_many(const void* value, size_t count);
template <typename T> inline T* alloc_space(size_t count);
ar<char> alloc_format(const char* format, ...);
ar<u8> load_file(const char* path);

#include "mutex.cpp"
#include "thread.cpp"
#include "ar.cpp"
#include "gar.cpp"
#include "types/size.cpp"
#include "types/f32.cpp"
#include "types/f64.cpp"
#include "types/u8.cpp"
#include "types/i8.cpp"
#include "types/u16.cpp"
#include "types/i16.cpp"
#include "types/u32.cpp"
#include "types/i32.cpp"
#include "types/u64.cpp"
#include "types/i64.cpp"
#include "vector/v2.cpp"
#include "vector/v3.cpp"
#include "vector/v4.cpp"
#include "matrix/m3.cpp"
#include "matrix/m4.cpp"

template <typename T> inline void swap(T* a, T* b) {
	T temp = *a;
	*a = *b;
	*b = temp;
}

template <typename T> inline T* alloc(T value) {
	T* ptr = alloc_space<T>(1);
	*ptr = value;
	return ptr;
}

template <typename T> inline T* alloc_many(const void* value, size_t count) {
	T* ptr = alloc_space<T>(count);
	std::memcpy(ptr, value, sizeof(T) * count);
	return ptr;
}

template <typename T> inline T* alloc_space(size_t count) {
	if (count == 0) {
		CTK_PANIC("count is zero");
	}
	T* ptr = (T*)std::malloc(sizeof(T) * count);
	if (ptr == nullptr) {
		CTK_PANIC("alloc_space failed");
	}
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

ar<u8> load_file(const char* path) {
	FILE* file = std::fopen(path, "rb");
	if (file == nullptr) {
		return ar<u8>();
	}
	std::fseek(file, 0, SEEK_END);
	long file_size = std::ftell(file);
	std::rewind(file);
	ar<u8> data = ar<u8>::create(file_size);
	size_t bytes_read = std::fread(data.buf, 1, file_size, file);
	if (bytes_read != file_size) {
		CTK_PANIC("std::fread failed");
	}
	std::fclose(file);
	return data;
}