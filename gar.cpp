template <typename T> struct gar {
	T* buf = nullptr;
	size_t len = 0;
	size_t cap = 0;

	void bound_check(size_t index) const;
	const T& operator [] (size_t index) const;
	T& operator [] (size_t index);
	static gar<T> create(size_t cap);
	static gar<T> create_auto();
	void destroy();
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

template <typename T> void gar<T>::bound_check(size_t index) const {
	if (index >= this->len) {
		CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
	}
}

template <typename T> const T& gar<T>::operator [] (size_t index) const {
#ifdef GAR_ABC
	bound_check(index);
#endif
	return this->buf[index];
}

template <typename T> T& gar<T>::operator [] (size_t index) {
#ifdef GAR_ABC
	bound_check(index);
#endif
	return this->buf[index];
}

template <typename T> gar<T> gar<T>::create(size_t cap) {
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

template <typename T> gar<T> gar<T>::create_auto() {
	return gar<T>::create(2);
}

template <typename T> void gar<T>::destroy() {
	std::free(this->buf);
	this->buf = nullptr;
}

template <typename T> void gar<T>::clear() {
	len = 0;
}

template <typename T> ar<T> gar<T>::to_ar() const {
	ar<T> array;
	array.buf = this->buf;
	array.len = this->len;
	return array;
}

template <typename T> gar<T> gar<T>::clone() const {
	gar<T> new_array = gar<T>::create(this->cap);
	new_array.len = this->len;
	std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
	return new_array;
}

template <typename T> void gar<T>::grow() {
	this->cap *= 2;
	this->buf = (T*)std::realloc(this->buf, sizeof(T) * this->cap);
	if (this->buf == nullptr) {
		CTK_PANIC("%s: realloc failed (cap:%zu)", __PRETTY_FUNCTION__, this->cap);
	}
}

template <typename T> void gar<T>::push(T value) {
	if (this->len == this->cap) {
		this->grow();
	}
	this->buf[this->len] = value;
	this->len += 1;
}

template <typename T> void gar<T>::push_many(const void* src_ptr, size_t count) {
	size_t old_len = len;
	this->len += count;
	while (this->len >= this->cap) {
		this->grow();
	}
	std::memcpy(&this->buf[old_len], src_ptr, sizeof(T) * count);
}

template <typename T> T gar<T>::pop() {
	if (this->len == 0) {
		CTK_PANIC("%s: len is zero", __PRETTY_FUNCTION__);
	}
	this->len -= 1;
	return this->buf[this->len];
}

template <typename T> void gar<T>::pop_many(size_t count) {
	if (this->len < count) {
		CTK_PANIC("%s: len is zero", __PRETTY_FUNCTION__);
	}
	this->len -= count;
}

template <typename T> void gar<T>::join(ar<T> other) {
	this->push_many(other.buf, other.len);
}

template <typename T> void gar<T>::join(gar<T> other) {
	this->push_many(other.buf, other.len);
}

template <typename T> void gar<T>::insert(size_t index, T value) {
	if (index > this->len) {
		CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
	}
	if (this->len == this->cap) {
		this->grow();
	}
	std::memmove(&this->buf[index + 1], &this->buf[index], sizeof(T) * (this->len - index));
	this->buf[index] = value;
	this->len += 1;
}

template <typename T> void gar<T>::insert_many(size_t index, const void* src_ptr, size_t count) {
	if (count == 0) {
		CTK_PANIC("%s: count is zero", __PRETTY_FUNCTION__);
	}
	if (index >= this->len) {
		CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
	}
	this->len += count;
	while (this->len >= this->cap) {
		this->grow();
	}
	std::memmove(&this->buf[index + count], &this->buf[index], sizeof(T) * (this->len - index - count));
	std::memcpy(&this->buf[index], src_ptr, sizeof(T) * count);
}

template <typename T> T gar<T>::remove(size_t index) {
	if (index >= this->len) {
		CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
	}
	T value = this->buf[index];
	this->len -= 1;
	std::memmove(&this->buf[index], &this->buf[index + 1], sizeof(T) * (this->len - index));
	return value;
}

template <typename T> void gar<T>::remove_many(size_t index, size_t count) {
	if (count == 0) {
		CTK_PANIC("%s: count is zero", __PRETTY_FUNCTION__);
	}
	if (index + count > this->len) {
		CTK_PANIC("%s: index %zu+%zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, count, this->len);
	}
	std::memmove(&this->buf[index], &this->buf[index + count], sizeof(T) * (this->len - index - count));
	this->len -= count;
}