# ifndef NB_OCCURENCES_MAX

#define NB_OCCURRENCES_MAX 100
#include <time.h>

/**
 * This method compute the class of the objects, using the k-means method.
 * The result will be EXIT_SUCCESS or EXIT_FAILURE.
 * @param objects : the objects to classify
 * @param method : the values we use, "GFD","F0","SA" or "E34"
 * @param res : The table used to stock the computed classes.
 */
int clustering(struct object * objects , char* method , int* res);



/*	!!!!!!!!!!!!!!!!!!!!!!!!!!!
 *   /!\ The next method musn't be called by the main function !!!
 *   They will be call by the function clustering !!!
 *  !!!!!!!!!!!!!!!!!!!!!!!!!!!
 *
*/





/**
 * This method compute the mean of a specific cluster
 * @param nbDimensions : The numbers of measures for each object (for example 16 if we use the E34 method)
 * @param values : The objects' measures
 * @param classes : The cluster of the objects (classes[i] = cluster of the object n∞i)
 * @param considered_class : The number of the studied cluster
 * @param res : The table where we must write the answer. (We used a table because the measures are multidimensionnal)
 *
 *
 * This function is called by all_means
 */
void mean(int nbDimensions , float **values , int* classes , int considered_class , float res[nbDimensions])  ;



/**
 * This method compute the mean of a each cluster
 * @param nbDimensions : The numbers of measures for each object (for example 16 if we use the E34 method)
 * @param values : The objects' measures
 * @param classes : The clusters of the objects (classes[i] = cluster of the object n∞i)
 * @param means : The table where we must write the answer. (A table of table)
 *
 * This function is called by kmeans
 *
 */
void allmeans(int nbDimensions , float **values , int* classes, float means[][nbDimensions]) ;



/**
 * This method returns the distance between two points A and B
 * @param pointA : coordinates of point A
 * @param pointB : coordinates of point B
 * @param nbDimensions : number of coordinates
 *
 * This function is called by class
 *
 * NB : In fact, we doesn't compute the distance but the square of the distance.
 * So, we don't need to call the function sqrt, so there is a step less.
 * Because we want only to compare distances, this doesn't change the result.
 */
float distance(float* pointA, float* pointB , int nbDimensions) ;




/**
 * This method returns the (provisional) estimated cluster of an object.
 * @param nbDimensions : The numbers of measures for the object (for example 16 if we use the E34 method)
 * @param value : The object's measures
 * @param means : The mean of each actual cluster
 *
 * This function is called by kmeans
 */
int class(int nbDimensions,float **value, float means[][nbDimensions])  ;



/**
 * This method execute the k-means algorithm
 * @param nbDimensions : The numbers of measures for the object (for example 16 if we use the E34 method)
 * @param values : The objects' measures
 * @param means : Used only to don't have to create a new table in each call of kmeans
 * @param classes : The actual estimate cluster of the objects (classes[i] = cluster of the object n∞i)
 * @param permitted_occurences : The max number of kmean's calls. Used to avoid infinite loop.
 * @param res : The table used to stock the computed classes.
 *
 * This function is called by itself (recursively) and by cluster
 */
void kmeans(int nbDimensions , float **values , float means[][nbDimensions], int* classes , int permitted_occurences , int* res)  ;





/**
 * This method initialize the kmeans algorithm
 * @param objects : the objects to classify
 * @param method : the values we use, "GFD","F0","SA" or "E34"
 * @param nbDimensions : The numbers of measures for the object, previously computed by clustering
 * @param res : The table used to stock the computed classes.
 *
 * This functoin is called by clustering
 */
void cluster(struct object * objects , char* method , int nbDimensions , int* res) ;


#endif
