/**
* This method calculate the euclidean distance
* @param coord_classified is the  classified object coordonates 
* @param new_object is the  object's coordonates  to be classified  
**/
float euclidean_distance(float coord_classified[], float coord_to_be_classified[], int MAX);


/**
*	The method compare two object's distance
* 	This method is used by internal c function qsort to sort data
*	@param cd1 fist distance
*   @param cd1 second distance 
**/
int compare(struct  class_distance* cd1,struct class_distance* cd2);


/**
* The method use all distance and classify the new object.
* This method is used by internal c function qsort to sort data
* @param c_d array of distance between classifieds objects and the new object to be classified
**/
int classify(struct class_distance* c_d);
