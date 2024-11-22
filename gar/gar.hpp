template <typename T>
struct gar {
	T* buf = nullptr;
	size_t len = 0;
	size_t cap = 0;

	void bound_check(size_t index) const;
	const T& operator [] (size_t index) const;
	T& operator [] (size_t index);
	static gar<T> alloc(size_t cap);
	void free();
	void clear();
	ar<T> to_ar() const;
	gar<T> clone() const;
	void grow();
	void push(T value);
	void push_many(const void* src_ptr, size_t count);
	T pop();
	void pop_many(size_t count);
	void join(ar<T> other);
	void join(gar<T> other);
	void insert(size_t index, T value);
	void insert_many(size_t index, const void* src_ptr, size_t count);
	T remove(size_t index);
	void remove_many(size_t index, size_t count);
};