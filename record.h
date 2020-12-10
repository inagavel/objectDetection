# ifndef RECORD


# include "header.h"

/**
 * Read the reals class of the objects, using the names
 * @param size : the number of objects
 * @param obj : the objects
 * @param res : the table used to stock the classes
 */
void expected_classes(int size , struct object obj[size] , int res[size]) ;


/**
 * Show the occurences of each class in the variable classes.
 * For example, if, after this fonction, res = {4,7,1,2,5,12,3,3,8} ,
 * this means the variable classes contains 4 times the class n°1 , 7 times the class n°2...
 *
 * @param size : the number of objects
 * @param classes : the number of class for each class from an object list
 * @param res : The table used to stock the occurences numbers
 */
void occurences_classes(int size , int classes[size] , int res[CLASS_NUMBER]) ;



/**
 * Return the success ratio (between 0.0 and 1.0) of the classification
 *
 * @param size : the number of classified objects
 * @param find_classes : the computed classes
 * @param expected_class : the real classes
 */
float success_ratio(int size , int find_classes[size] , int expected_class[size]) ;





/**
 * Return the success ratio (between 0.0 and 1.0) of the classification
 *
 * The diference with the previous function is that if some class have a bad name,
 * it isn't count as an error
 * (for example, if each object on class 2 are computed as class 3 and vice-versa)
 *
 * @param size : the number of classified objects
 * @param find_classes : the computed classes
 * @param expected_class : the real classes
 */
float success_ratio_only_groups(int size , int find_classes[size] , int expected_class[size]) ;




#define RECORD

#endif