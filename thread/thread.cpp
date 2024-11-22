#include "thread.hpp"

void Thread::try_join() {
	if (this->running) {
		this->running = false;
		pthread_join(this->id, nullptr);
	}
}