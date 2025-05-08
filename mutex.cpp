struct Mutex {
#ifdef CTK_WIN32
	CRITICAL_SECTION critical_section;
#endif
#ifdef CTK_LINUX
	pthread_mutex_t pthread_mutex;
#endif

	static Mutex create();
	void destroy();
	void lock();
	void unlock();
};

#ifdef CTK_WIN32
Mutex Mutex::create() {
	Mutex mutex;
	::InitializeCriticalSection(&mutex.critical_section);
	return mutex;
}

void Mutex::destroy() {
	::DeleteCriticalSection(&this->critical_section);
}

void Mutex::lock() {
	::EnterCriticalSection(&this->critical_section);
}

void Mutex::unlock() {
	::LeaveCriticalSection(&this->critical_section);
}
#endif

#ifdef CTK_LINUX
Mutex Mutex::create() {
	Mutex mutex;
	pthread_mutex_init(&mutex.pthread_mutex, nullptr);
	return mutex;
}

void Mutex::destroy() {
	pthread_mutex_destroy(&this->pthread_mutex);
}

void Mutex::lock() {
	pthread_mutex_lock(&this->pthread_mutex);
}

void Mutex::unlock() {
	pthread_mutex_unlock(&this->pthread_mutex);
}
#endif