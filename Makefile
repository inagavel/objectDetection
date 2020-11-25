all: launcher

launcher: launcher.o classification_manager.o file_manager.o algo_k_nearest_neighbor.o
	gcc  launcher.o classification_manager.o file_manager.o algo_k_nearest_neighbor.o -o launcher

launcher.o: launcher.c 
	gcc -c launcher.c 

classification_manager.o: classification_manager.c
	gcc -c classification_manager.c 

file_manager.o: file_manager.c
	gcc -c file_manager.c 

algo_k_nearest_neighbor: algo_k_nearest_neighbor.c
	gcc -c algo_k_nearest_neighbor.c

clean: 
	rm *.o launcher
do:
	./launcher
