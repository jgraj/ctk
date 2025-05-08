struct FileWriter {
	FILE* file = nullptr;

	static FileWriter open(const char* file_path) {
		FileWriter writer;
		writer.file = std::fopen(file_path, "wb");
		return writer;
	}

	void close() {
		if (this->file == nullptr) {
			return;
		}
		std::fclose(this->file);
		this->file = nullptr;
	}

	template <typename T> void write_many(const T* src_ptr, size_t count) {
		size_t write_count = std::fwrite(src_ptr, sizeof(T), count, this->file);
		if (write_count == 0 || write_count < count) {
			CTK_PANIC("std::fwrite failed");
		}
	}

	template <typename T> void write(T value) {
		this->write_many(&value, 1);
	}

	template <typename T> void write_ar32(ar<T> array) {
		this->write<u32>(array.len);
		if (array.len != 0) {
			this->write_many<T>(array.buf, array.len);
		}
	}
};