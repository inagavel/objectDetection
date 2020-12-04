

#include "header.h"
#include "algo_clustering.h"



# define NB_OCCURRENCES_MAX 1000




void mean(int nbDimensions , float values[][nbDimensions] , int* classes , int considered_class , float res[nbDimensions]) {

	int n = 0 ;
	int i,j ;

	for(i = 0 ; i<nbDimensions ; i++)
		res[i] = 0.0 ;


	for(i = 0 ; i<PICTURES_NUMBER ; i++) {

		if(classes[i]==considered_class)  {

			n++ ;

			for(j = 0 ; j<nbDimensions ; j++) {
				res[j] += values[i][j] ;
			}

		}

	}



	for(i = 0 ; i<nbDimensions ; i++) {

		res[i] /= n ;

	}


}


void allmeans(int nbDimensions , float values[][nbDimensions] , int* classes, float means[][nbDimensions]) {
	for(int i = 1 ; i<=CLASS_NUMBER ; i++) {
		mean(nbDimensions,values,classes,i,means[i-1]) ;
	}
}



int nb_occurences(int classes[PICTURES_NUMBER], int considered_class) {
	int n = 0 ;
	for(int i=0 ; i<PICTURES_NUMBER ; i++) {
		if(classes[i] == considered_class) {
			n++ ;
		}
	}
	return n ;
}






float distance(float* pointA, float* pointB , int nbDimensions) {

	float res = 0.0 ;

	for(int i = 0 ; i<nbDimensions ; i++) {
		res += pow((pointA[i]-pointB[i]),2) ;
	}

	return res ;

}


int class(int nbDimensions,float value[nbDimensions], float means[][nbDimensions]) {
	int res = 1 ;
	float dist = distance(value,means[0],nbDimensions) ;
	float new_dist ;
	for(int i=1 ; i<CLASS_NUMBER ; i++) {
		new_dist = distance(value,means[i],nbDimensions) ;
		if(new_dist<dist) {
			dist = new_dist ;
			res = i+1 ;
		}
	}
	return res ;
}








void kmeans(int nbDimensions , float values[][nbDimensions] , float means[][nbDimensions], int* classes , int permitted_occurences , int* res) {



	allmeans(nbDimensions,values,classes,means) ;

	short identique = 1 ;
	int classe ;

	for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
		classe = class(nbDimensions,values[i],means) ;
		identique = (identique && (classes[i]==classe)) ;
		classes[i] = classe ;
	}


	if((permitted_occurences==0) || identique) {

		for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
			res[i] = classes[i] ;
		}

	}

	else {
		kmeans(nbDimensions,values,means,classes,permitted_occurences-1,res) ;
	}

}





void cluster(struct object * objects , char* method , int nbDimensions , int* res) {


	float values[PICTURES_NUMBER][nbDimensions] ;

	if (strcmp(method, "E34") == 0)
	{
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].e34[j] ;
			}
		}
	}
	else if (strcmp(method, "F0") == 0)
	{
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].f0[j] ;
			}
		}
	}
	else if (strcmp(method, "GFD") == 0)
	{
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].gdf[j] ;
			}
		}
	}
	else if (strcmp(method, "SA") == 0)
	{
		for(int i = 0 ; i<PICTURES_NUMBER ; i++)  {
			for(int j = 0 ; j<nbDimensions ; j++) {
				values[i][j] = objects[i].sa[j] ;
			}
		} ;
	}


	int first_classes[PICTURES_NUMBER] ;

	for(int i = 0 ; i<PICTURES_NUMBER ; i++) {
		first_classes[i] = 0 ;
	}




	srand(time(NULL)) ;

	/* NB : We choose here a random number which will never be used
	 * because of a bug which choose always the same first number.
	 */
	int alea = (int)(rand() / (double)RAND_MAX * PICTURES_NUMBER) ;

	for(int i = 1 ; i<=CLASS_NUMBER ; i++) {
		do {
			alea = (int)(rand() / (double)RAND_MAX * PICTURES_NUMBER) ;
			if(first_classes[alea]==0)
				first_classes[alea] = i ;
		} while(first_classes[alea] != i) ;
	}

	float means[CLASS_NUMBER][nbDimensions] ;

	kmeans(nbDimensions,values,means,first_classes,NB_OCCURRENCES_MAX,res) ;


}



int clustering(struct object * objects , char* method , int* res) {

	int nbDimensions ;

	if (strcmp(method, "E34") == 0)
	{
		nbDimensions = E34_MAX ;
	}
	else if (strcmp(method, "F0") == 0)
	{
		nbDimensions = F0_MAX ;
	}
	else if (strcmp(method, "GFD") == 0)
	{
		nbDimensions = GDF_MAX ;
	}
	else if (strcmp(method, "SA") == 0)
	{
		nbDimensions = SA_MAX ;
	}
	else {
		printf("The method %s doesn't exist", method) ;
		return EXIT_FAILURE ;
	}

	cluster(objects,method,nbDimensions,res) ;

	return EXIT_SUCCESS ;
}








