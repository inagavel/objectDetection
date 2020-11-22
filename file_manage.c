#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h> 



#define TAILLE_MAX   10000 // Tableau de taille 10000`
#define NAME_MAX     50 // Tableau de taille 10000`
#define E34_MAX      16 // Tableau de taille 10000`
#define F0_MAX       128 // Tableau de taille 10000`
#define GDF_MAX      100 // Tableau de taille 10000`
#define SA_MAX       90 // Tableau de taille 10000`
#define FILE_NUMBER  10000 // Tableau de taille 10000`
#define CLASS_NUMBER 9 // Tableau de taille 10000`
#define TRAINNING_NUMBER 11 // Tableau de taille 10000`

struct object{
	char *name;
	float e34[E34_MAX];
	float f0[F0_MAX];
	float gdf[GDF_MAX];
	float sa[SA_MAX];
};

void get_file_names(const char* dirpath, char** files)
{
  DIR *d;
  char  filesname[CLASS_NUMBER*TRAINNING_NUMBER][1000]; 
  struct dirent *dir;

  
 	char* dir1= (char *) malloc(1 + strlen(dirpath));
	strcpy(dir1,dirpath);
	printf("dir %s\n", dir1);
	    	

  d = opendir(dir1);
  if (d)
  {
  	int nbrFile=0;
  	char * ptr;
  	int    ch = 's';
  	int j =0;
    while ((dir = readdir(d)) != NULL) {

    	ptr = strchr( dir->d_name, ch );
    	if(ptr != NULL) // skip the . and .. files in Unix OS
    	{	
    		
    		int i =0;
    			    	
	    	while(dir->d_name[i]!= '.')
	    	{
	    		filesname[nbrFile][i]=dir->d_name[i];
	    		FILE* fichier = NULL;
	    		char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
	    		//int a =read_file(finalpath,chaine,dir,&data);
	    	  	i++;
	    	}
	    	
	    	filesname[nbrFile][i]='\0';
	    	files[nbrFile] = filesname[nbrFile];
	    	//printf("files %s\n", files[j]);
	    	
	    	nbrFile++;
	    	j++;
	    }
	   
    }
    closedir(d);
  }
}

int read_file(char* filepath, char* line, char* method,struct object *data)
{
	FILE* file = NULL;
	
	//filepath = finalpath;
	// Check file existence
	int returnval;
	returnval = access (filepath, F_OK);
	if (returnval == 0)
	{
		//printf ("\n %s exists\n", strvar);
		int returnval;
	    file = fopen(filepath, "r");
	 	
	    if (file != NULL)
	    {
	    	int i = 0;
	        while(fgets(line, TAILLE_MAX, file)) // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
	       	{	
	       		store_data(line,data, method,&i);
	       		printf("%s", line); // On affiche la chaîne 
	        	i++;	
	        }

	        fclose(file);
	    }
	 	
	 	else
	    {
	       // On affiche un message d'erreur si on veut
	       printf("Impossible d'ouvrir le fichier test.txt");
	    }
	}
	else
	{
		if (errno == ENOENT)
			printf ("%s No such file or directory.\n", filepath);
		else if (errno == EACCES)
			printf ("%s Permission denied.\n", filepath);
		exit(1);
	}
    return 0;
}

int store_data(char* line,  struct object *data, char *method, int *i)
{
	if (strcmp(method, "E34") == 0) 
	{
	 
	  data->e34[*i] = atof(line);
	} 
	else if (strcmp(method, "F0") == 0)
	{
	}
	else if (strcmp(method, "GFD") == 0)
	{
	}
	else if (strcmp(method, "SA") == 0)
	{
	}
	/* more else if clauses */
	else /* default: */
	{
		printf("METHOD NOT FOUND");
	}

	return 0;
}

int main(int argc, char *argv[])
{
	struct object data[CLASS_NUMBER*TRAINNING_NUMBER];
	FILE* fichier = NULL;
	char  chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX

	char* dirpath[]  = {"E34","F0","GFD","SA"};
	char** filesname= (char **) malloc(CLASS_NUMBER*TRAINNING_NUMBER*11); 
	char* separator = "/";
	
	char* format= (char *) malloc(1 + strlen(dirpath[0])+ strlen(separator));
	strcpy(format,".");
	strcat(format, dirpath[0]);
	char* dir = (char *) malloc(1 + strlen(dirpath[0])+ strlen(separator));	
	strcpy(dir, dirpath[0]);
	strcat(dir, separator);
	get_file_names(dir,filesname);
	char * finalpath = (char *) malloc(1 + strlen(dir)+ sizeof(filesname[0])+strlen(format));

	strcpy(finalpath, dir);
	strcat(finalpath, filesname[0]);
	strcat(finalpath, format);

	data[0].name = filesname[0];
	
	int a =read_file(finalpath,chaine,dirpath[0],&data[0]);
	int i = 0;
	printf("Name : %s\n", data[0].name); // On affiche la chaîne 
	

	i=0;
	while(i < E34_MAX)
	{
		printf("data : %f\n", data[0].e34[i]); // On affiche la chaîne 
		i++;
	}
    return 0;
}