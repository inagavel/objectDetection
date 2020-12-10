
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <math.h>

#include "header.h"
#include "classification_manager.h"

void get_file_names(const char* dirpath, char** files)
{
  DIR *d;
  char  filesname[CLASS_NUMBER*TRAINNING_NUMBER][10000]; 
  struct dirent *dir;

  
 	char* dir1= (char *) malloc(1 + strlen(dirpath));
	strcpy(dir1,dirpath);
	    	

  d = opendir(dir1);
  if (d)
  {
  	int nbrFile=0;
  	char * ptr;
  	int    ch = 's';
  	int j =0;
  	int k=0;
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
	    	  	i++;
	    	}
	    	
	    	filesname[nbrFile][i]='\0';
	    	files[nbrFile] = filesname[nbrFile];
	    	nbrFile++;
	    	j++;
	    }
	    
	    k++;
	    
    }
    closedir(d);
  }
}



int read_file(char* filepath, char* line, char* method,struct object *data)
{

	FILE* file = NULL;
	
	
	int returnval;
	returnval = access (filepath, F_OK);
	if (returnval == 0)
	{
		int returnval;
	    file = fopen(filepath, "r");
	 	
	    if (file != NULL)
	    {
	    	int i = 0;
	        while(fgets(line, TAILLE_MAX, file)) // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
	       	{	
	       		add_method_data(line,data, method,&i);
	        	i++;	
	        }

	        fclose(file);
	    }
	 	
	 	else
	    {
	       // On affiche un message d'erreur si on veut
	       printf("We Can not open the test file.txt");
	       exit(1);
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