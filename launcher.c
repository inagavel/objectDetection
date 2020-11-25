
#include "header.h"
#include "classification_manager.h"
#include "file_manager.h"
#include "algo_k_nearest_neighbor.h"

int main(int argc, char *argv[])
{
	struct object data[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object classifieddata[CLASS_NUMBER*3];
	struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object datatoclassify[CLASS_NUMBER*TRAINNING_NUMBER - CLASS_NUMBER*3];
	FILE* fichier = NULL;
	char  chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

	char* dirpath[]  = {"E34","F0","GFD","SA"};
	char** filesname= (char **) malloc(CLASS_NUMBER*TRAINNING_NUMBER*11); 
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
	
	int i =0;
	initialize_training_class(allclass);
	add_object(data,allclass,datatoclassify);

	struct  class_distance c_d[CLASS_NUMBER*3];
	i=0;
	k=0;
	int j = 0;
	while (i < CLASS_NUMBER)
	{
		j = 0;
		while (j < 3)
		{
			c_d[k].distance =  euclidean_distance(allclass[i].element[j]->sa,datatoclassify[10].sa);
			c_d[k].tc.name = allclass[i].name;
			c_d[k].id = allclass[i].id;
			
			j++;
			k++;
		}
		i++;
	}

	i = 0;

	qsort((void*)&c_d,CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);	
	printf("AFETER SORT\n");
	i = 0;
	printf("%s\n",datatoclassify[10].name);
    while (i < CLASS_NUMBER*3)
	{
		printf("%d   %s %f\n",i+1,c_d[i].tc.name, c_d[i].distance);
		i++;
	}
	classify(c_d);
    return 0;
}