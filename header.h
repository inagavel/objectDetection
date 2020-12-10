#ifndef  TAILLE_MAX
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <math.h>

#define TAILLE_MAX       10000 
#define NAME_MAX         50 
#define E34_MAX          16 
#define F0_MAX           128 
#define GFD_MAX          100 
#define METHOD_MAX       100 
#define SA_MAX           90 
#define FILE_NUMBER      10000 
#define CLASS_NUMBER     9 
#define TRAINNING_NUMBER 11
//#define K 4
#define PICTURES_NUMBER 99
#define TRUE_POSITIVE 0 
#define TRUE_NEGATIVE 1 
#define FALSE_POSITIVE 2 
#define FALSE_NEGATIVE 3 
typedef enum  {E34 , F0 , GFD , SA} method ;
typedef int (*compfn)(const void*, const void*);

struct object{
	char *name;
	float e34[E34_MAX];
	float f0[F0_MAX];
	float gfd[GFD_MAX];
	float sa[SA_MAX];
};

struct training_class{
	char *name;
	struct object *element[CLASS_NUMBER];
	int id;
};

struct class_distance{
	struct training_class tc;
	float distance;
	int id;
};
#endif