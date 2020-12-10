
#include "header.h"
#include "classification_manager.h"
#include "file_manager.h"
#include "algo_k_nearest_neighbor.h"
#include "algo_clustering.h"
#include "record.h"

int classes_e34[72];
int classes_f0[72];
int classes_gfd[72];
int classes_sa[72];

int classify_with_k_nearest_neighbor(struct training_class classifieddata[CLASS_NUMBER*TRAINNING_NUMBER], struct object datatoclassify[],int indexObject);
int classify_with_clustering(struct object datatoclassify[]);
void show_class(int * classes, struct object* datatoclassify);
float ratio_reslut(int * classes,struct object * datatoclassify);
float ratio_result_cluster(int * classes,struct object ** datatoclassify);

int main(int argc, char *argv[])
{
	//int indexObject = 72;
	struct object data[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object classifieddata[CLASS_NUMBER*4];
	struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object  datatoclassify[CLASS_NUMBER*TRAINNING_NUMBER+20];
	struct object datatoclassify_clustering[PICTURES_NUMBER];

	
	FILE* fichier = NULL;
	char  chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

	char* dirpath[]  = {"E34","F0","GFD","SA"};
	char** filesname= (char **) malloc(CLASS_NUMBER*TRAINNING_NUMBER*50); 
	char* separator = "/";
	
	char* format= (char *) malloc(1 + strlen(dirpath[0])+ strlen(separator));
	

	char* dir = (char *) malloc(1 + strlen(dirpath[0])+ strlen(separator));
	int k =0;

	strcpy(dir, dirpath[0]);
	strcat(dir, separator);
	get_file_names(dir,filesname);

	
	while(k < 4)
	{
		strcpy(dir, dirpath[k]);
		strcat(dir, separator);

		int i=0;
		int j=0;
		while(filesname[i]!= NULL)
		{
			char * finalpath = (char *) malloc(1 + strlen(dir)+ sizeof(filesname[i])+strlen(format));
			strcpy(finalpath, dir);
			strcat(finalpath, filesname[i]);
			strcpy(format,".");
			strcat(format, dirpath[k]);
			strcat(finalpath, format);

			data[i].name = filesname[i];
			read_file(finalpath,chaine,dirpath[k],&data[i]);
			
			j++;
			i++;
		}

		k++;
	}
	
	initialize_training_class(allclass);
	int indexArray [CLASS_NUMBER*3+10];

	add_object(data,allclass,datatoclassify,indexArray);

	int choice = 1;
	if(choice == 1)
	{
		for(int j =0  ; j< PICTURES_NUMBER - 3 * CLASS_NUMBER; j++)
		{

			classify_with_k_nearest_neighbor(allclass,datatoclassify,j);
			printf("--------------------------------------------\n");
		}
	}	
	else
	{
		int i=0;
		int j=0;
		int k=0;


		for( i = 0 ; i < CLASS_NUMBER; i++)
		{
			for(j = 0 ; j < 3; j++)
			{
				datatoclassify_clustering[k++] = *allclass[i].element[j];
			}
		}
		
		for(j=0; j< PICTURES_NUMBER - CLASS_NUMBER*3; j++)
		{
			datatoclassify_clustering[k++] = datatoclassify[j];
		}

		printf("START clusting");
		classify_with_clustering(datatoclassify_clustering);
		printf("FINISH clusting");

	}
	int i =0;


	

	//show_class(classes_e34,datatoclassify);
		printf("----------------------------------\n");
		printf("E34 : %f\n", ratio_reslut(classes_e34,datatoclassify));
		printf("F0  : %f\n", ratio_reslut(classes_f0,datatoclassify));
		printf("GFD : %f\n", ratio_reslut(classes_gfd,datatoclassify));
		printf("SA  : %f\n", ratio_reslut(classes_sa,datatoclassify));
		printf("----------------------------------\n");
	
	// RATIO

	
	

    return 0;
}

/*
float ratio_result_cluster(int * classes,struct object ** datatoclassify)
{
	int total = PICTURES_NUMBER;
	int expected_class[total];
	expected_classes(total,datatoclassify,expected_class);
	return success_ratio_only_groups(total,classes,expected_class);
}*/

float ratio_reslut(int * classes,struct object * datatoclassify)
{
	int total = PICTURES_NUMBER - 3 * CLASS_NUMBER;
	int expected_class[total];
	expected_classes(total,datatoclassify,expected_class);
	return success_ratio(total,classes,expected_class);
}

void show_class(int * classes, struct object* datatoclassify)
{
	for(int j =0  ; j<PICTURES_NUMBER -3 * CLASS_NUMBER ; j++)
	{
		printf("%d , %s  \n",classes[j],datatoclassify[j].name) ;

	}
}

int classify_with_clustering(struct object datatoclassify[]){

	int classes[PICTURES_NUMBER] ;
	char * usedMethod ;
	int realclass[PICTURES_NUMBER] ;
	int expected_class[PICTURES_NUMBER];
	//expected_classes(PICTURES_NUMBER,datatoclassify,expected_class);


	for(int i = 2 ; i < 3 ; i++)
	{

		switch(i)
		{
			case 0  : usedMethod = "E34" ; printf("E34 method : \n") ; break ;
			case 1  : usedMethod = "F0" ; printf("F0 method : \n") ; break ;
			case 2  : usedMethod = "GFD" ; printf("GFD method : \n") ; break ;
			case 3  : usedMethod = "SA" ; printf("SA method : \n") ; break ;
			default : printf("IL Y A UNE ERREUR !!!!!!! \n") ; return EXIT_FAILURE ;
		}

		//struct object  new_datatoclassify[CLASS_NUMBER*TRAINNING_NUMBER];

		//memcpy(new_datatoclassify, datatoclassify, CLASS_NUMBER*TRAINNING_NUMBER);
		//new_datatoclassify = datatoclassify;
		
		for(int j =0  ; j<PICTURES_NUMBER ; j++)
		{
			//new_datatoclassify[j] = datatoclassify[j];
			printf("%d , %s %d \n",j,datatoclassify[j].name, classes[j]) ;

		}

		int buffer = clustering(datatoclassify,usedMethod,classes);
		printf("APRES 1 : clustering\n");
		if(buffer == EXIT_SUCCESS)
		{
			printf("APRES 2: clustering\n");
			for(int j =0  ; j<PICTURES_NUMBER ; j++)
			{

				printf("%d , %s %d \n",j,datatoclassify[j].name, classes[j]) ;

			}

			printf("\n\n\n") ;

			
			//float f =0.f;// success_ratio_only_groups(PICTURES_NUMBER,classes,expected_class);
			//float f = ratio_result_cluster(classes,datatoclassify);
			//printf("CLUSTERING RATIO: %f USING: %s\n",f,usedMethod);

		}
		else
			printf("ERROR\n");
			
	}
	return 0;
}

int classify_with_k_nearest_neighbor(struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER],struct object datatoclassify[],int indexObject)
{
	struct  class_distance c_d_e34[CLASS_NUMBER*3];
	struct  class_distance c_d_f0 [CLASS_NUMBER*3];
	struct  class_distance c_d_gfd[CLASS_NUMBER*3];
	struct  class_distance c_d_sa [CLASS_NUMBER*3];
/*
	struct class_distance * c_d_gfd;
	c_d_gfd = malloc(CLASS_NUMBER*3 * sizeof(struct class_distance*));
*/
	printf("\nclassify_with_k_nearest_neighbor\n");
	
	int b = indexObject;	
	int i = 0;
	int k = 0;
	int j = 0;
	//int indexClass=0;


	while (i < CLASS_NUMBER)
	{

		j = 0;
		while (j < 3)
		{
			c_d_e34[k].distance  =  euclidean_distance(allclass[i].element[j]->e34 ,datatoclassify[indexObject].e34, E34_MAX);
			c_d_f0[k].distance   =  euclidean_distance(allclass[i].element[j]->f0  ,datatoclassify[indexObject].f0 ,  F0_MAX);
			c_d_gfd[k].distance  =  euclidean_distance(allclass[i].element[j]->gfd ,datatoclassify[indexObject].gfd, GFD_MAX);
			c_d_sa[k] .distance  =  euclidean_distance(allclass[i].element[j]->sa  ,datatoclassify[indexObject].sa ,  SA_MAX);
			
			c_d_e34[k].tc.name   = allclass[i].element[j]->name;
			c_d_e34[k].id        = allclass[i].id;

			c_d_f0[k].tc.name    = allclass[i].element[j]->name;
			c_d_f0[k].id         = allclass[i].id;

			c_d_gfd[k].tc.name   = allclass[i].element[j]->name;
			c_d_gfd[k].id        = allclass[i].id;

			c_d_sa[k].tc.name    = allclass[i].element[j]->name;
			c_d_sa[k].id         = allclass[i].id;
			
			j++;
			k++;
		}
		i++;
	}
	/*printf("before sirt\n");
	for(int j =0  ; j<PICTURES_NUMBER - CLASS_NUMBER*3; j++)
		{
			printf("%d , %s \n",j,datatoclassify[j].name) ;

		}
*/
	qsort((void*)&c_d_e34, CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_f0 , CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_gfd, CLASS_NUMBER*3,sizeof(struct class_distance), (compfn)compare);
	qsort((void*)&c_d_sa , CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);

	//printf("after sort sirt\n");
	printf("%d : %s\n",indexObject,datatoclassify[indexObject].name);
	i = 0;
	printf("\nMETHOD E34\n");

  	 while (i < K)
	{
		printf("name :  %s    %f\n", c_d_e34[i].tc.name, c_d_e34[i].distance);
		i++;
	}

	classes_e34[indexObject] = classify(c_d_e34);

	printf("\nMETHOD F0\n");
	printf("%d : %s\n",indexObject,datatoclassify[indexObject].name);
	i = 0;
	while (i < K)
	{
		printf("name :  %s    %f\n", c_d_f0[i].tc.name, c_d_f0[i].distance);
		i++;
	}

	classes_f0[indexObject] = classify(c_d_f0);

	printf("\nMETHOD GFD\n");
	printf("\nindexObject  : %d\n",indexObject);
	printf("%d : %s \n",indexObject,datatoclassify[indexObject].name);
	i = 0;
	while (i < K)
	{
		printf("name :  %s    %f\n", c_d_gfd[i].tc.name, c_d_gfd[i].distance);
		i++;
	}

	classes_gfd[indexObject] = classify(c_d_gfd);

	i = 0;
	printf("\nMETHOD SA\n");
	while (i < K)
	{
		printf("name :  %s    %f\n", c_d_sa[i].tc.name, c_d_sa[i].distance);
		i++;
	}
	classes_sa[indexObject] = classify(c_d_sa); 
	
	printf("\nFINISH 2 WITH SUCCESS\n");
	return 0;
}