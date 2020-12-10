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
	# first launch k-plus-proche-voisiens
	# last k-means
	 ./launcher 1 1 4 0 
	# ./launcher  1 
	#  param 1 : 1 for knn algo or 2 for clustering
	#  param 2 : method to use
	#  param 3 : K value
	#  param 4 : display step details 1 or not 0
