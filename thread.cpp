struct Thread {
	struct Arg {
		void (*func)(void*);
		void* arg;
	};

#ifdef CTK_WIN
	HANDLE handle;
#endif
#ifdef CTK_LIN
	pthread_t id;
#endif

	static Thread create(void (*func)(void*), void* arg);
	void join();
	void detach();
};

#ifdef CTK_WIN
DWORD WINAPI bootstrap(LPVOID param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	std::free(thread_arg);
	return 0;
}

Thread Thread::create(void (*func)(void*), void* arg) {
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg(func, arg));
	Thread thread;
	thread.handle = ::CreateThread(nullptr, 0, bootstrap, thread_arg, 0, nullptr);
	if (thread.handle == nullptr) {
		CTK_PANIC("CreateThread failed");
	}
	return thread;
}

void Thread::join() {
	if (::WaitForSingleObject(this->handle, INFINITE) != WAIT_OBJECT_0) {
		CTK_PANIC("WaitForSingleObject failed");
	}
	::CloseHandle(this->handle);
}

void Thread::detach() {
	::CloseHandle(this->handle);
}
#endif

#ifdef CTK_LIN
void* bootstrap(void* param) {
	Thread::Arg* thread_arg = (Thread::Arg*)param;
	thread_arg->func(thread_arg->arg);
	std::free(thread_arg);
	return nullptr;
}

Thread Thread::create(void (*func)(void*), void* arg) {
	Thread::Arg* thread_arg = alloc<Thread::Arg>(Thread::Arg(func, arg));
	Thread thread;
	if (::pthread_create(&thread.id, nullptr, bootstrap, thread_arg) != 0) {
		CTK_PANIC("pthread_create failed");
	}
	return thread;
}

void Thread::join() {
	::pthread_join(this->id, nullptr);
}

void Thread::detach() {
	::pthread_detach(this->id);
}
#endif