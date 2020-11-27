
#include "header.h"
#include "classification_manager.h"
#include "file_manager.h"
#include "algo_k_nearest_neighbor.h"

int main(int argc, char *argv[])
{
	printf("%s", argv[1]);
	int indexObject = 72;
	struct object data[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object classifieddata[CLASS_NUMBER*3];
	struct training_class allclass[CLASS_NUMBER*TRAINNING_NUMBER];
	struct object datatoclassify[CLASS_NUMBER*TRAINNING_NUMBER - CLASS_NUMBER*3];

	struct  class_distance c_d_e34[CLASS_NUMBER*3];
	struct  class_distance c_d_f0 [CLASS_NUMBER*3];
	struct  class_distance c_d_gdf[CLASS_NUMBER*3];
	struct  class_distance c_d_sa [CLASS_NUMBER*3];
			
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
	i=0;
	k=0;
	int j = 0;

	while (i < CLASS_NUMBER)
	{
		j = 0;
		while (j < 3)
		{
			c_d_e34[k].distance  =  euclidean_distance(allclass[i].element[j]->e34,datatoclassify[indexObject].e34,E34_MAX);
			c_d_f0[k].distance   =  euclidean_distance(allclass[i].element[j]->f0 ,datatoclassify[indexObject].f0 , F0_MAX);
			c_d_gdf[k].distance  =  euclidean_distance(allclass[i].element[j]->gdf,datatoclassify[indexObject].gdf,GDF_MAX);
			c_d_sa[k] .distance  =  euclidean_distance(allclass[i].element[j]->sa ,datatoclassify[indexObject].sa , SA_MAX);
			
			c_d_e34[k].tc.name      = allclass[i].name;
			c_d_e34[k].id           = allclass[i].id;

			c_d_f0[k].tc.name      = allclass[i].name;
			c_d_f0[k].id           = allclass[i].id;

			c_d_gdf[k].tc.name      = allclass[i].name;
			c_d_gdf[k].id           = allclass[i].id;

			c_d_sa[k].tc.name      = allclass[i].name;
			c_d_sa[k].id           = allclass[i].id;
			
			j++;
			k++;
		}
		i++;
	}

	qsort((void*)&c_d_e34,CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_f0 ,CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_gdf,CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);
	qsort((void*)&c_d_sa ,CLASS_NUMBER*3,sizeof(struct class_distance),(compfn)compare);

	printf("AFETER SORT\n");
	i = 0;
	printf("METHOD E34\n");
	printf("%s\n",datatoclassify[indexObject].name);

    while (i < 10)
	{
		//printf("%d name  %s\n",i+1, c_d_e34[i].tc.name);
		printf("name :  %s    %f\n", c_d_e34[i].tc.name, c_d_e34[i].distance);
		i++;
	}

	classify(c_d_e34);

	printf("METHOD F0\n");
	i = 0;
	 while (i < 10)
	{
		//printf("%d name  %s\n",i+1, c_d_e34[i].tc.name);
		printf("name :  %s    %f\n", c_d_f0[i].tc.name, c_d_f0[i].distance);
		i++;
	}

	classify(c_d_f0);

	printf("METHOD GDF\n");
	i = 0;
	 while (i < 10)
	{
		//printf("%d name  %s\n",i+1, c_d_e34[i].tc.name);
		printf("name :  %s    %f\n", c_d_gdf[i].tc.name, c_d_gdf[i].distance);
		i++;
	}

	classify(c_d_gdf);

	i = 0;
	printf("METHOD SA\n");
	 while (i < 10)
	{
		//printf("%d name  %s\n",i+1, c_d_e34[i].tc.name);
		printf("name :  %s    %f\n", c_d_sa[i].tc.name, c_d_sa[i].distance);
		i++;
	}

	classify(c_d_sa);
	
    return 0;
}