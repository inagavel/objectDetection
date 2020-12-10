all: launcher

launcher: launcher.o classification_manager.o file_manager.o algo_k_nearest_neighbor.o algo_clustering.o record.o
	 gcc  launcher.o classification_manager.o file_manager.o algo_k_nearest_neighbor.o algo_clustering.o record.o -o launcher

launcher.o: launcher.c 
	gcc -c launcher.c 

classification_manager.o: classification_manager.c
	gcc -c classification_manager.c 

file_manager.o: file_manager.c
	gcc -c file_manager.c 

algo_k_nearest_neighbor.o: algo_k_nearest_neighbor.c
	gcc -c algo_k_nearest_neighbor.c

algo_clustering.o: algo_clustering.c
	gcc -c algo_clustering.c

record.o: record.c
	gcc -c record.c



clean: 
	rm *.o launcher
do:
	./launcher 
