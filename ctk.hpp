constexpr f64 pi = 3.14159265358979323846;
constexpr f64 deg2rad = pi / 180.0;
constexpr f64 rad2deg = 180.0 / pi;

template <typename T> inline void swap(T* a, T* b);
template <typename T> inline T* alloc();
template <typename T> inline T* alloc_copy(T value);
template <typename T> inline T* alloc_many(size_t count);
template <typename T> inline T* alloc_many_copy(const void* value, size_t count);
ar<char> alloc_format(const char* format, ...);