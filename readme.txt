

Deux façon de lancer l'application
	1 - si automake est installé sur le pc pour utiliser le makefile
		1- make clean   : efface tous les binaires
		2- make all    : compile le programme
		3- make do     : lance l'application
	2 -  sans makefile :

	 1- gcc -c launcher.c classification_manager.c file_manager.c algo_k_nearest_neighbor.c algo_clustering.c record.c

	 2- gcc  launcher.o classification_manager.o file_manager.o algo_k_nearest_neighbor.o algo_clustering.o record.o -o launcher

	pour  lancer l'application il faut juste commenter ou decomenter
	 # ./launcher 1 1 4 0 
	 # ./launcher  1 

	#  param 1 : 1 for knn algo or 2 for clustering
	#  param 2 : method to use
	#  param 3 : K value
	#  param 4 : display step details 1 or not 0


Les commentaires sont dans les fichiers .h
