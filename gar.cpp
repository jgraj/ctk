template <typename T>
struct gar;

template <typename T>
struct ar {
	T* buf = nullptr;
	size_t len = 0;

	void bound_check(size_t index) const {
		if (index >= this->len) {
			CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
		}
	}

	const T& operator [] (size_t index) const {
#ifdef GAR_ABC
		bound_check(index);
#endif
		return this->buf[index];
	}

	T& operator [] (size_t index) {
		bound_check(index);
		return this->buf[index];
	}

	static ar<T> alloc(size_t len) {
		if (len == 0) {
			CTK_PANIC("%s: len is zero", __PRETTY_FUNCTION__);
		}
		ar<T> array;
		array.len = len;
		array.buf = (T*)std::malloc(sizeof(T) * len);
		if (array.buf == nullptr) {
			CTK_PANIC("%s: malloc failed (len:%zu)", __PRETTY_FUNCTION__, len);
		}
		return array;
	}

	void free() {
		std::free(this->buf);
		this->buf = nullptr;
	}

	void clear() {
		this->len = 0;
	}

	gar<T> to_gar() const;

	ar<T> clone() const {
		ar<T> new_array = alloc(this->len);
		std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		return new_array;
	}

	ar<T> resize_clone(size_t new_len) const {
		ar<T> new_array = alloc(new_len);
		if (this->len != 0) {
			std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		}
		return new_array;
	}
};

template <typename T>
struct gar {
	T* buf = nullptr;
	size_t len = 0;
	size_t cap = 0;

	void bound_check(size_t index) const {
		if (index >= this->len) {
			CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
		}
	}

	const T& operator [] (size_t index) const {
#ifdef GAR_ABC
		bound_check(index);
#endif
		return this->buf[index];
	}

	T& operator [] (size_t index) {
#ifdef GAR_ABC
		bound_check(index);
#endif
		return this->buf[index];
	}

	static gar<T> alloc(size_t cap) {
		if (cap == 0) {
			CTK_PANIC("%s: cap is zero", __PRETTY_FUNCTION__);
		}
		gar<T> array;
		array.len = 0;
		array.cap = cap;
		array.buf = (T*)std::malloc(sizeof(T) * cap);
		if (array.buf == nullptr) {
			CTK_PANIC("%s: malloc failed (cap:%zu)", __PRETTY_FUNCTION__, cap);
		}
		return array;
	}

	void free() {
		std::free(this->buf);
		this->buf = nullptr;
	}

	void clear() {
		len = 0;
	}

	ar<T> to_ar() const {
		ar<T> array;
		array.buf = this->buf;
		array.len = this->len;
		return array;
	}

	gar<T> clone() const {
		gar<T> new_array = alloc(this->cap);
		new_array.len = this->len;
		std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
		return new_array;
	}

	void grow() {
		this->cap *= 2;
		this->buf = (T*)std::realloc(this->buf, sizeof(T) * this->cap);
		if (this->buf == nullptr) {
			CTK_PANIC("%s: realloc failed (cap:%zu)", __PRETTY_FUNCTION__, this->cap);
		}
	}

	void push(T value) {
		if (this->len == this->cap) {
			this->grow();
		}
		this->buf[this->len] = value;
		this->len += 1;
	}

	void push_many(T* src_ptr, size_t count) {
		size_t old_len = len;
		this->len += count;
		while (this->len >= this->cap) {
			this->grow();
		}
		std::memcpy(&this->buf[old_len], src_ptr, sizeof(T) * count);
	}

	T pop() {
		if (this->len == 0) {
			CTK_PANIC("%s: len is zero", __PRETTY_FUNCTION__);
		}
		this->len -= 1;
		return this->buf[this->len];
	}

	void pop_many(size_t count) {
		if (this->len < count) {
			CTK_PANIC("%s: len is zero", __PRETTY_FUNCTION__);
		}
		this->len -= count;
	}

	void join(ar<T> other) {
		this->push_many(other.buf, other.len);
	}

	void join(gar<T> other) {
		this->push_many(other.buf, other.len);
	}

	void insert(size_t index, T value) {
		if (index >= this->len) {
			CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
		}
		if (this->len == this->cap) {
			this->grow();
		}
		std::memmove(&this->buf[index + 1], &this->buf[index], sizeof(T) * (this->len - index));
		this->buf[index] = value;
		this->len += 1;
	}

	void insert_many(size_t index, T* src_ptr, size_t count) {
		if (count == 0) {
			CTK_PANIC("%s: count is zero", __PRETTY_FUNCTION__);
		}
		if (index + count > this->len) {
			CTK_PANIC("%s: index %zu+%zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, count, this->len);
		}
		this->len += count;
		while (this->len >= this->cap) {
			this->grow();
		}
		std::memmove(&this->buf[index + count], &this->buf[index], sizeof(T) * (this->len - index - count));
		std::memcpy(&this->buf[index], src_ptr, sizeof(T) * count);
	}

	T remove(size_t index) {
		if (index >= this->len) {
			CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
		}
		T value = this->buf[index];
		this->len -= 1;
		std::memmove(&this->buf[index], &this->buf[index + 1], sizeof(T) * (this->len - index));
		return value;
	}

	void remove_many(size_t index, size_t count) {
		if (count == 0) {
			CTK_PANIC("%s: count is zero", __PRETTY_FUNCTION__);
		}
		if (index + count > this->len) {
			CTK_PANIC("%s: index %zu+%zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, count, this->len);
		}
		std::memmove(&this->buf[index], &this->buf[index + count], sizeof(T) * (this->len - index - count));
		this->len -= count;
	}
};

template <typename T>
gar<T> ar<T>::to_gar() const {
	gar<T> array;
	array.buf = this->buf;
	array.len = this->len;
	array.cap = this->cap;
	return array;
}