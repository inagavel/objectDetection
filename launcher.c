
#include "header.h"
#include "classification_manager.h"
#include "file_manager.h"
#include "algo_k_nearest_neighbor.h"
#include "algo_clustering.h"
#include "record.h"
#include "launcher.h"


int classes_e34[72];
int classes_f0[72];
int classes_gfd[72];
int classes_sa[72];
int K=4;
bool showknnstep= false;

int main(int argc, char *argv[])
{
	int choice;
	if(argc == 5)
	{
		choice = (int) strtol(argv[1], NULL, 10);
		K= (int) strtol(argv[3], NULL, 10);
		printf("K : %d", K);
		if((int) strtol(argv[4], NULL, 10) == 1)
		{
			showknnstep = true; 
		}
	}
	else if(argc == 1)
	{
		choice = 2;
		if((int) strtol(argv[1], NULL, 10) == 1)
		{
			showknnstep = true; 
		}
	}

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

	if(choice == 1)
	{

		printf("\nSTART k_nearest_neighbor classification\n");
		
		printf("+-----+------------+--------+--------+--------+--------+\n");
		printf("|  N° |    OBJECT  |   E34  |   F0   |   GFD  |   SA   |\n");		
		printf("+-----+------------+--------+--------+--------+--------+\n");
		for(int j =0  ; j< PICTURES_NUMBER - 3 * CLASS_NUMBER; j++)
		{
			classify_with_k_nearest_neighbor(allclass,datatoclassify,j,K);
		}

		printf("\nFINISH 2 k_nearest_neighbor WITH SUCCESS\n");
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

		printf("\nSTART clusting - Kmeans\n");
		classify_with_clustering(datatoclassify_clustering);

	}
	int i =0;


	

	//show_class(classes_e34,datatoclassify);
		
	
	// RATIO
	printf("K = %d\n", K);
	if(choice == 1)
	{

		int total = PICTURES_NUMBER - 3 * CLASS_NUMBER;
		int expected_class[total];
		expected_classes(total,datatoclassify,expected_class);
		
		
		int confusionE34[CLASS_NUMBER][4];	
		int confusionF0 [CLASS_NUMBER][4];	
		int confusionGFD[CLASS_NUMBER][4];	
		int confusionSA [CLASS_NUMBER][4];	

		confusion_matrice(total,classes_e34 ,expected_class , confusionE34) ;
		printf("\n\nMETHOD EA34 \n");
		printf("+--------+-------+-------+-------+-------+\n");
		printf("| CLASS  |  T/P  |  T/N  |  F/P  |  F/N  |\n");		
		printf("+--------+-------+-------+-------+-------+\n");

		for(int j =0  ; j<CLASS_NUMBER ; j++)
		{
			//printf("+-----+------------+--------+--------+--------+\n");
			printf("|   %.2d   |  %.2d   |   %.2d  |  %.2d  |    %.2d  |\n",(j+1),confusionE34[j][TRUE_POSITIVE],confusionE34[j][TRUE_NEGATIVE],confusionE34[j][FALSE_POSITIVE],confusionE34[j][FALSE_NEGATIVE]);		
			printf("+--------+-------+------+--------+-------+\n");
		}
		confusion_matrice(total,classes_f0  ,expected_class , confusionF0) ;

		printf("\n\nMETHOD F0 \n");
		printf("+--------+-------+-------+-------+-------+\n");
		printf("| CLASS  |  T/P  |  T/N  |  F/P  |  F/N  |\n");		
		printf("+--------+-------+-------+-------+-------+\n");

		for(int j =0  ; j<CLASS_NUMBER ; j++)
		{
			printf("|   %.2d   |  %.2d   |   %.2d  |  %.2d  |    %.2d  |\n",(j+1),confusionF0[j][TRUE_POSITIVE],confusionF0[j][TRUE_NEGATIVE],confusionF0[j][FALSE_POSITIVE],confusionF0[j][FALSE_NEGATIVE]) ;
			printf("+--------+-------+------+--------+-------+\n");
		}
			confusion_matrice(total,classes_gfd ,expected_class , confusionGFD) ;
		printf("\n\nMETHOD GFD \n");
		printf("+--------+-------+-------+-------+-------+\n");
		printf("| CLASS  |  T/P  |  T/N  |  F/P  |  F/N  |\n");		
		printf("+--------+-------+-------+-------+-------+\n");


		for(int j =0  ; j<CLASS_NUMBER ; j++)
		{
			printf("|   %.2d   |  %.2d   |   %.2d  |  %.2d  |    %.2d  |\n",(j+1),confusionGFD[j][TRUE_POSITIVE],confusionGFD[j][TRUE_NEGATIVE],confusionGFD[j][FALSE_POSITIVE],confusionGFD[j][FALSE_NEGATIVE]) ;
			printf("+--------+-------+------+--------+-------+\n");
		}

		confusion_matrice(total,classes_sa  ,expected_class , confusionSA) ;

		printf("\n\nMETHOD SA \n");
		printf("+--------+-------+-------+-------+-------+\n");
		printf("| CLASS  |  T/P  |  T/N  |  F/P  |  F/N  |\n");		
		printf("+--------+-------+-------+-------+-------+\n");


		for(int j =0  ; j<CLASS_NUMBER ; j++)
		{
			printf("|   %.2d   |  %.2d   |   %.2d  |  %.2d  |    %.2d  |\n",(j+1),confusionSA[j][TRUE_POSITIVE],confusionSA[j][TRUE_NEGATIVE],confusionSA[j][FALSE_POSITIVE],confusionSA[j][FALSE_NEGATIVE]) ;
			printf("+--------+-------+------+--------+-------+\n");
		}

		//success_ratio(total,classes_e34,expected_class);
		float rE34 = success_ratio(total,classes_e34,expected_class)*100;
		float rF0  = success_ratio(total,classes_f0,expected_class) *100;
		float rGFD = success_ratio(total,classes_gfd,expected_class)*100;
		float rSA  = success_ratio(total,classes_sa,expected_class) *100;

		printf("\n\nGLOBAL RATIO \n");
		printf("+------------+---------+---------+---------+---------+\n");
		printf("|  METHOD    |    E34  |    F0   |    GFD  |    SA   |\n");		
		printf("+------------+---------+---------+---------+---------+\n");
		printf("|  RATIO     |  %.2f  |  %.2f  |  %.2f  |   %.2f |\n",rE34,rF0,rGFD,rSA);	
		printf("+------------+---------+---------+---------+---------+\n");
		printf("\n\n\n\n");
	}

	else
	{

	}
	

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

float ratio_result(int * classes,struct object * datatoclassify)
{
	
	return 0.0;
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
	expected_classes(PICTURES_NUMBER,datatoclassify,expected_class);

	int classArray[4][PICTURES_NUMBER];
	/*int **classArray;
	classArray = malloc(4 * sizeof(int*));
	for(int j = 0 ; j < PICTURES_NUMBER ; j++) {
		classArray[j] =	malloc(sizeof(int));
	}*/

	float *ratioAray;
	ratioAray = malloc(4 * sizeof(float*));

	//float ratioAray[PICTURES_NUMBER];

/*	
	printf("+-----+------------+--------+--------+--------+--------+\n");
	printf("|  N° |    OBJECT  |   E34  |   F0   |   GFD  |   SA   |\n");		
	printf("+-----+------------+--------+--------+--------+--------+\n");
*/
	int confusion[CLASS_NUMBER][4];
	for(int i = 0 ; i <4 ; i++)
	{
		switch(i)
		{
			case 0  : usedMethod = "E34"; break ;
			case 1  : usedMethod = "F0" ; break ;
			case 2  : usedMethod = "GFD";break ;
			case 3  : usedMethod = "SA" ;  break ;
			default : printf("IL Y A UNE ERREUR !!!!!!! \n") ; return EXIT_FAILURE ;
		}

		int buffer = clustering(datatoclassify,usedMethod,classes);

	
		if(buffer == EXIT_SUCCESS)
		{
			for(int j =0  ; j<PICTURES_NUMBER ; j++)
			{
				classArray[i][j] =classes[j];
				//printf("%d , %s %d \n",j,datatoclassify[j].name, classes[j]) ;

			}
			if(showknnstep)
			{
				printf("APRES 2: clustering\n");
				
			
				printf("\n\n\n") ;
			}

			change_classes(PICTURES_NUMBER,classes,expected_class);
			ratioAray[i] = success_ratio(PICTURES_NUMBER,classes,expected_class);
			confusion_matrice(PICTURES_NUMBER,classes ,expected_class , confusion) ;

			//float f = ratio_result_cluster(classes,datatoclassify);
			//printf("CLUSTERING RATIO: %f USING: %s\n",f,usedMethod);

			//int occurences[CLASS_NUMBER];

			//occurences_classes( PICTURES_NUMBER,classes ,occurences) ;
			/*
			for(int j =0  ; j<CLASS_NUMBER ; j++)
			{
				//printf("class : %d ,  occurence :%d \n",classes[j], occurences[j]) ;
				printf("%d éléments dans la classe %d\n",occurences[j],(j+1));
			}
	*/
			printf("\n\nMETHOD %s \n",usedMethod);
			printf("+--------+-------+-------+-------+-------+\n");
			printf("| CLASS  |  T/P  |  T/N  |  F/P  |  F/N  |\n");		
			printf("+--------+-------+-------+-------+-------+\n");
			for(int j =0  ; j<CLASS_NUMBER ; j++)
			{
				printf("|   %.2d   |  %.2d   |   %.2d  |  %.2d  |    %.2d  |\n",(j+1),confusion[j][TRUE_POSITIVE],confusion[j][TRUE_NEGATIVE],confusion[j][FALSE_POSITIVE],confusion[j][FALSE_NEGATIVE]) ;
				printf("+--------+-------+------+--------+-------+\n");
			}
				
			printf("\n\n\n");
				
		}
		else
			printf("ERROR\n");
	}
/*
	for(int j =0  ; j<PICTURES_NUMBER ; j++)
	{
		printf("| %.2d  |  %s   |    %d   |    %d   |    %d   |   %d    |\n",j+1,datatoclassify[j].name, classArray[0][j],classArray[1][j],classArray[2][j],classArray[3][j]);	
		printf("+-----+------------+--------+--------+--------+--------+\n");
	}
*/
	printf("+------------+---------+---------+---------+---------+\n");
	printf("|  METHOD    |    E34  |    F0   |    GFD  |    SA   |\n");		
	printf("+------------+---------+---------+---------+---------+\n");
	printf("|  RATIO     |   %.2f  |  %.2f   |   %.2f  |   %.2f  |\n",ratioAray[0],ratioAray[1],ratioAray[2],ratioAray[3]);	
	printf("+------------+---------+---------+---------+---------+\n");


	return 0;
}

/*
int classify_with_k_nearest_neighbor(struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER],struct object datatoclassify[],int indexObject)
{
	printf("A");
	struct  class_distance c_d[CLASS_NUMBER*3];
	struct  class_distance c_d_e34[CLASS_NUMBER*3];
	struct  class_distance c_d_f0 [CLASS_NUMBER*3];
	struct  class_distance c_d_gfd[CLASS_NUMBER*3];
	struct  class_distance c_d_sa [CLASS_NUMBER*3];

	printf("\nclassify_with_k_nearest_neighbor\n");
	
	int i = 0;
	int k = 0;
	int j = 0;
	printf("B");
	while (i < CLASS_NUMBER)
	{

		j = 0;
		while (j < 3)
		{
			c_d[k].distance  =  euclidean_distance(allclass[i].element[j]->e34 ,datatoclassify[indexObject].e34, E34_MAX);
			c_d[k].tc.name   = allclass[i].element[j]->name;
			c_d[k].id        = allclass[i].id;
			j++;
			k++;
		}
		i++;
	}
	printf("AFTER SORT");
	qsort((void*)&c_d, CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	
	classes_e34[indexObject] = classify(c_d_e34);	
	
	show_knn_step_classi(datatoclassify[indexObject].name, "E34",c_d,classes_e34[indexObject],indexObject);
	
	printf("\nFINISH 2 WITH SUCCESS\n");
	return 0;
}
*/

int classify_with_k_nearest_neighbor(struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER],struct object datatoclassify[],int indexObject, int K)
{
	struct  class_distance c_d_e34[CLASS_NUMBER*3];
	struct  class_distance c_d_f0 [CLASS_NUMBER*3];
	struct  class_distance c_d_gfd[CLASS_NUMBER*3];
	struct  class_distance c_d_sa [CLASS_NUMBER*3];

	
	
	int b = indexObject;	
	int i = 0;
	int k = 0;
	int j = 0;
	
	while (i < CLASS_NUMBER)
	{

		j = 0;
		while (j < 3)
		{
			c_d_e34[k].distance  =  euclidean_distance(allclass[i].element[j]->e34 ,datatoclassify[indexObject].e34, E34_MAX);
			c_d_f0[k] .distance  =  euclidean_distance(allclass[i].element[j]->f0  ,datatoclassify[indexObject].f0 ,  F0_MAX);
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
	
	qsort((void*)&c_d_e34, CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_f0 , CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_gfd, CLASS_NUMBER*3,sizeof(struct class_distance), (compfn)compare);
	qsort((void*)&c_d_sa , CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);

	int rE34 = classify(c_d_e34,K);	
	int rF0  = classify(c_d_f0,K);
	int rGFD = classify(c_d_gfd,K);
	int rSA  = classify(c_d_sa,K); 
	classes_e34[indexObject] = rE34;
	classes_f0[indexObject]  = 	rF0;
	classes_gfd[indexObject] = rGFD;
	classes_sa[indexObject]  = rSA;

	printf("| %.2d  |  %s   |    %d   |    %d   |    %d   |   %d    |\n",indexObject+1,datatoclassify[indexObject].name, rE34,rF0,rGFD,rSA);	
	printf("+-----+------------+--------+--------+--------+--------+\n");

	if(showknnstep)
	{
		show_knn_step_classi(datatoclassify[indexObject].name, "E34",c_d_e34,rE34,indexObject);
		show_knn_step_classi(datatoclassify[indexObject].name, "F0" ,c_d_f0,rF0 ,indexObject);
		show_knn_step_classi(datatoclassify[indexObject].name, "GFD",c_d_gfd,rGFD,indexObject);
		show_knn_step_classi(datatoclassify[indexObject].name, "SA" ,c_d_sa,rSA ,indexObject);
	}
	return 0;
}


void show_knn_step_classi(char *name, char* method, struct  class_distance* c_d_e34,int class,int indexObject)
{
	printf("%d : %s\n",indexObject,name);
	printf("\nMETHOD : %s\n",method);	

	int i = 0;
  	 while (i < K)
	{
		printf("name :  %s    %f\n", c_d_e34[i].tc.name, c_d_e34[i].distance);
		i++;
	}

	printf("CLASSIFIED TO %d : \n",class);
}