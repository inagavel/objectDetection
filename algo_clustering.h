# ifndef NB_OCCURENCES_MAX

#define NB_OCCURRENCES_MAX 100
#include <time.h>

/**
 * This method compute the class of the objects, using the k-means method
 * @param objects : the objects to classify
 * @parma method : the values we use, "GFD","F0","SA" or "E34"
 * @param res : The table used to stock the computed classes.
 */
int clustering(struct object * objects , char* method , int* res);

#endif