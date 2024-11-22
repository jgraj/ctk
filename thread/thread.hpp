struct Thread {
	pthread_t id;
	bool running = true;

	void try_join();
};