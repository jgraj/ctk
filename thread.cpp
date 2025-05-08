struct Thread {
	struct Arg {
		void (*func)(void*);
		void* arg;
	};

#ifdef CTK_WIN32
	HANDLE handle;
#endif
#ifdef CTK_LINUX
	pthread_t id;
#endif
	bool exists = false;

	void create(void (*func)(void*), void* arg);
	void join();
	bool try_join();
	void detach();
};

#ifdef CTK_WIN32
DWORD WINAPI bootstrap(LPVOID param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	std::free(thread_arg);
	return 0;
}

void Thread::create(void (*func)(void*), void* arg) {
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg(func, arg));
	Thread thread;
	this->handle = ::CreateThread(nullptr, 0, bootstrap, thread_arg, 0, nullptr);
	if (this->handle == nullptr) {
		CTK_PANIC("CreateThread failed");
	}
}

void Thread::join() {
	if (this->exists == false) {
		return;
	}
	if (::WaitForSingleObject(this->handle, INFINITE) != WAIT_OBJECT_0) {
		CTK_PANIC("WaitForSingleObject failed");
	}
	::CloseHandle(this->handle);
	this->exists = false;
}

bool Thread::try_join() {
	if (this->exists == false) {
		return true;
	}
	DWORD wait_value = ::WaitForSingleObject(this->handle, 0);
	if (wait_value == WAIT_FAILED) {
		CTK_PANIC("WaitForSingleObject failed");
	}
	if (wait_value == WAIT_OBJECT_0) {
		this->exists = false;
		return true;
	}
	return false;
}

void Thread::detach() {
	::CloseHandle(this->handle);
}
#endif

#ifdef CTK_LINUX
void* bootstrap(void* param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	std::free(thread_arg);
	return nullptr;
}

void Thread::create(void (*func)(void*), void* arg) {
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg(func, arg));
	int pthread_create_ret = ::pthread_create(&this->id, nullptr, bootstrap, thread_arg);
	if (pthread_create_ret == 0) {
		this->exists = true;
	} else {
		this->exists = false;
	}
}

void Thread::join() {
	if (this->exists == false) {
		return;
	}
	::pthread_join(this->id, nullptr);
	this->exists = false;
}

bool Thread::try_join() {
	if (this->exists == false) {
		return true;
	}
	int join_value = ::pthread_tryjoin_np(this->id, nullptr);
	if (join_value == 0) {
		this->exists = false;
		return true;
	}
	return false;
}

void Thread::detach() {
	::pthread_detach(this->id);
}
#endif