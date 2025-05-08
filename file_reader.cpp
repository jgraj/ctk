struct FileReader {
	FILE* file = nullptr;

	static FileReader open(const char* file_path) {
		FileReader reader;
		reader.file = std::fopen(file_path, "rb");
		return reader;
	}

	void close() {
		if (this->file == nullptr) {
			return;
		}
		std::fclose(this->file);
		this->file = nullptr;
	}

	template <typename T> void read_many(T* dst_ptr, size_t count) {
		size_t read_count = std::fread(dst_ptr, sizeof(T), count, this->file);
		if (read_count == 0 || read_count < count) {
			CTK_PANIC("std::fread failed");
		}
	}

	template <typename T> T read() {
		T value;
		this->read_many(&value, 1);
		return value;
	}

	template <typename T> ar<T> read_ar32() {
		u32 array_len = this->read<u32>();
		if (array_len == 0) {
			return ar<T>();
		}
		ar<T> array = ar<T>::create(array_len);
		this->read_many<T>(array.buf, array_len);
		return array;
	}
};