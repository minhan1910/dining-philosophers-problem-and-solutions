.PHONY: semaphore even_odd

semaphore:
	gcc semaphore.c -o semaphore -lpthread
	./semaphore
even_odd: 
	gcc even_odd.c -o even_odd -lpthread
	./even_odd
clean:
	rm -rf *.o even_odd semaphore 
