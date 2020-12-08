
/**
* this method store a coordonate to a specific method in object
* @param line the file line where is the coordonate
* @param an_object the object where to store le coordonate
* @param method the method of classifiction
* @param i the index to store the coordonate
**/
int add_method_data(char* line,  struct object *an_object, char *method, int *i);


/**
* this method verify if str1 contains a substring of str2
* @parm str1 the main string
* @parm str2 the substring
**/
bool contains(char* str1,char* str2);


/**
* this method add an object to training class array or to test objets array
* @param an_object the object to be stored
* @param training_objects training object array
* @param test_objects test object array
**/
int add_start_data(struct object* an_object,struct object* training_objects, struct object *test_objects);

/**
* This method initialize the trainng classs array
* @param allclass the array to store the training objects
**/
int initialize_training_class(struct training_class* allclass);


/**
* This method initialize the trainng array
* @param an_object the object to be added
* @param training_objects training object array
* @param test_objects test object array
**/
int add_object(struct object* an_object, struct training_class* allclass, struct object* test_objects);