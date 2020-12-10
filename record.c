# include "record.h"


int expected_classe(struct object obj) {

	int res = 0 ;

	char* string = obj.name ;
	int i = 0 ;

	while(string[i]<'0' || string[i]>'9')
		i++ ;

	while(string[i]>='0' && string[i]<='9') {
		res = 10 * res + (string[i] - '0') ;
		i++ ;
	}

	return res ;

}



void expected_classes(int size , struct object obj[size] , int res[size]) {
	for(int i=0 ; i<size ; i++) {
		res[i] = expected_classe(obj[i]) ;
	}
}



void occurences_classes(int size , int classes[size] , int res[CLASS_NUMBER]) {

	int i ;

	for(i = 0 ; i<CLASS_NUMBER ; i++)
		res[i] = 0 ;

	for(i = 0 ; i<size ; i++) {
		res[classes[i]-1]++ ;
	}

}



float success_ratio(int size , int find_classes[size] , int expected_class[size]) {

	float res = 0.0 ;

	for(int i = 0 ; i<size ; i++) {
		if(find_classes[i] == expected_class[i])
			res++ ;
	}

	return res/size ;

}





void reals_classes(int size , int find_classes[size] , int expected_class[size] , int studied_class , int res[CLASS_NUMBER]) {

	int i ;
	for(i = 0 ; i<CLASS_NUMBER ; i++)
		res[i] = 0 ;

	int max = 0 ;
	int real_class ;

	for(i = 0 ; i<size ; i++) {
		if(find_classes[i] == studied_class) {
			real_class = expected_class[i] ;
			res[real_class-1]++ ;
			if(res[real_class-1] > max)
				max++ ;
		}
	}


	for(i = 0 ; i<CLASS_NUMBER ; i++)
		res[i] = max-res[i] ;

}



short only_one(int tab[CLASS_NUMBER]) {
	for(int i = 0 ; i<CLASS_NUMBER ; i++) {
		if(tab[i] != 1)
			return 0 ;
	}
	return 1 ;
}
void change_classes(int size , int find_classes[size] , int expected_class[size]) {
	int i,j ;
	int used_classes[CLASS_NUMBER] ;
	int replace[CLASS_NUMBER] ;

	for(i = 0 ; i<CLASS_NUMBER ; i++)
		used_classes[i] = 0 ;


	/*
	 * the_reals_class[i][j] (when the values will be computed)
	 * will be almost the number of objects identified as class n∞(i+1)
	 * whereas they are from class n∞(j+1)
	 *
	 * In fact, this value will be the difference between this number
	 * and the biggest j for this i.
	 *
	 * For example, if the_real_class[i] = {1,3,0,2,7} ,
	 * it means that, in the objects identified as class (i+1),
	 * the majority are in fact from class 3 (because the 3rd value is 0).
	 *
	 * There are here 7 objects more in class 3 than in class 5
	 * (because the majority as from class 3 and the 5th value is 7).
	 */
	int the_real_classes[CLASS_NUMBER][CLASS_NUMBER] ;


	for(i = 0 ; i<CLASS_NUMBER ; i++) {

		reals_classes(size,find_classes,expected_class,(i+1),the_real_classes[i]) ;
		j = 0 ;

		// We found the max
		while(the_real_classes[i][j] > 0)
			j++ ;

		used_classes[j]++ ;
		replace[i] = j+1 ;

	}



	int class0 , class2 , rankclass2 , rankclass2bis ;

	while(!(only_one(used_classes))) {


		//We found a class used 0 times
		class0=0 ;
		while(used_classes[class0]>0)
			class0++ ;



		class2 = -1 ;


		for(i = 0 ; i<CLASS_NUMBER ; i++) {

			if(used_classes[i]>1) {

				if(class2 == -1) {
					class2 = i ;
					rankclass2 = the_real_classes[i][class0] ;
				}
				else {
					rankclass2bis = the_real_classes[i][class0] ;

					if(rankclass2bis < rankclass2) {
						class2 = i ;
						rankclass2 = rankclass2bis ;
					}
				}

			}

		}


		used_classes[class0]++ ;
		used_classes[class2]-- ;
		replace[class2] = class0 + 1 ;


	}



	for(i = 0 ; i<size ; i++)
		find_classes[i] = replace[(find_classes[i])-1] ;

}

void confusion_matrice(int size, int finded_classes[size] , int expected_classes[size] , int res[CLASS_NUMBER][4]) {

	/*float **values;
	values = malloc(PICTURES_NUMBER * sizeof(float*));
	for(int j = 0 ; j < PICTURES_NUMBER ; j++) {
		values[j] =	malloc(nbDimensions * sizeof(float));
	}*/

	int i,j,classeF,classeE ;

	for(i=0 ; i<size ; i++) {
		for(j=0 ; j<4 ; j++) {
			res[i][j] = 0 ;
		}
	}

	int tp = TRUE_POSITIVE ;
	int tn = TRUE_NEGATIVE ;
	int fp = FALSE_POSITIVE ;
	int fn = FALSE_NEGATIVE ;

	for(i=0 ; i<size ; i++) {
		for(j=0 ; j<4 ; j++) {
			res[i][j] = 0 ;
		}
	}


	for(i = 0 ; i<size ; i++) {

		classeF = finded_classes[i] ;
		classeE = expected_classes[i] ;

		if(classeE == classeF) {

			for(j=0 ; j<CLASS_NUMBER ; j++) {

				if(j+1 == classeE)
					res[j][tp]++ ;

				else
					res[j][tn]++ ;

			}

		}

		else {

			for(j=0 ; j<CLASS_NUMBER ; j++) {

				if(j+1 == classeE)
					res[j][fn]++ ;

				else if(j+1 == classeF)
					res[j][fp]++ ;

				else
					res[j][tn]++ ;

			}

		}

	}

}