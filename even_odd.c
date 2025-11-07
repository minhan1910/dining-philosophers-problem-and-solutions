#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define num_philosophers 5
#define num_forks 5

pthread_mutex_t forks[num_forks];

void think(int id) {
	printf("id %d Thinking...\n", id);
	sleep(1);
}

void* worker(void* arg) {
	int id = *(int *)arg;
	int right_id = (id + 1) % num_forks;

	if (id % 2 == 0) {
		// pick left 
		printf("even id %d get left fork %d\n", id, id);
		pthread_mutex_lock(&forks[id]);
		// pick right
		printf("even id %d get right fork %d\n", id, right_id);
		pthread_mutex_lock(&forks[right_id]);
	} else {
		// pick right
		printf("odd id %d get right fork %d\n", id, right_id);
		pthread_mutex_lock(&forks[right_id]);
		// pick left
		printf("odd id %d get left fork %d\n", id, id);
		pthread_mutex_lock(&forks[id]);
	}

	think(id);

	// A thread may unlock a mutex only if it currently owns it
	pthread_mutex_unlock(&forks[id]);
	pthread_mutex_unlock(&forks[right_id]);
	return NULL;
}

int main() {
	pthread_t threads[num_philosophers];
	pthread_t ids[num_philosophers];
	
	for (int i = 0; i < num_forks; ++i) {
		pthread_mutex_init(&forks[i], NULL);
	}

	for (int i = 0; i < num_philosophers; ++i) {
		ids[i] = i;
		pthread_create(&threads[i], NULL, worker, &ids[i]); 
	}

	for (int i = 0; i < num_philosophers; ++i) {
		pthread_join(threads[i], NULL);
	}

	for (int i = 0; i < num_forks; ++i) {
		pthread_mutex_destroy(&forks[i]);
	}

	printf("All dones");

	return 0;
}
