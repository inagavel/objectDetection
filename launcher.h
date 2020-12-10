#include "header.h"

int classify_with_k_nearest_neighbor(struct training_class classifieddata[CLASS_NUMBER*TRAINNING_NUMBER], struct object datatoclassify[],int indexObject,int k);
int classify_with_clustering(struct object datatoclassify[]);
void show_class(int * classes, struct object* datatoclassify);
float ratio_result(int * classes,struct object * datatoclassify);
float ratio_result_cluster(int * classes,struct object ** datatoclassify);
void show_knn_step_classi(char *name, char* method, struct  class_distance* c_d_e34,int class,int indexObject );
