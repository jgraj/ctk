template <typename T> struct ar {
	T* buf = nullptr;
	size_t len = 0;

	void bound_check(size_t index) const;
	const T& operator [] (size_t index) const;
	T& operator [] (size_t index);
	static ar<T> create(size_t len);
	void destroy();
	void clear();
	gar<T> to_gar() const;
	ar<T> clone() const;
	ar<T> resize_clone(size_t new_len) const;
};

template <typename T> void ar<T>::bound_check(size_t index) const {
	if (index >= this->len) {
		CTK_PANIC("%s: index %zu is out of bounds (len:%zu)", __PRETTY_FUNCTION__, index, this->len);
	}
}

template <typename T> const T& ar<T>::operator [] (size_t index) const {
#ifdef GAR_ABC
	bound_check(index);
#endif
	return this->buf[index];
}

template <typename T> T& ar<T>::operator [] (size_t index) {
#ifdef GAR_ABC
	bound_check(index);
#endif
	return this->buf[index];
}

template <typename T> ar<T> ar<T>::create(size_t len) {
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

template <typename T> void ar<T>::destroy() {
	std::free(this->buf);
	this->buf = nullptr;
}

template <typename T> void ar<T>::clear() {
	this->len = 0;
}

template <typename T> gar<T> ar<T>::to_gar() const {
	gar<T> array;
	array.buf = this->buf;
	array.len = this->len;
	array.cap = this->len;
	return array;
}

template <typename T> ar<T> ar<T>::clone() const {
	ar<T> new_array = ar<T>::create(this->len);
	std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
	return new_array;
}

template <typename T> ar<T> ar<T>::resize_clone(size_t new_len) const {
	ar<T> new_array = ar<T>::create(new_len);
	if (this->len != 0) {
		std::memcpy(new_array.buf, this->buf, sizeof(T) * this->len);
	}
	return new_array;
}