.PHONY: semaphore even_odd clean run_semaphore run_even_odd

semaphore: semaphore.c
	gcc semaphore.c -o semaphore -lpthread

even_odd: even_odd.c
	gcc even_odd.c -o even_odd -lpthread

run_semaphore: semaphore
	./semaphore

run_even_odd: even_odd
	./even_odd

clean:
	rm -rf *.o even_odd semaphore 
