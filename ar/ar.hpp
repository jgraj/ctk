template <typename T>
struct ar {
	T* buf = nullptr;
	size_t len = 0;

	void bound_check(size_t index) const;
	const T& operator [] (size_t index) const;
	T& operator [] (size_t index);
	static ar<T> alloc(size_t len);
	void free();
	void clear();
	gar<T> to_gar() const;
	ar<T> clone() const;
	ar<T> resize_clone(size_t new_len) const;
};