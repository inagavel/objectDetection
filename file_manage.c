#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>



#define TAILLE_MAX 1000 // Tableau de taille 1000
 
int main(int argc, char *argv[])
{
		// Combine 2 Chars
	FILE* fichier = NULL;
	char* filepath = "E34/";
	int returnval;
	char * strvar="s01n001.E34";
	char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
	printf("\nProvide a name of the file or directory:\n");
	//fgets (strvar, 100, stdin);
	/*const char* n = "\n"	;
	strtok(strvar, n);
	*/
	// Combine 2 Chars
	char * finalpath = (char *) malloc(1 + strlen(filepath)+ strlen(strvar) );
	strcpy(finalpath, filepath);
	strcat(finalpath, strvar);
	filepath = finalpath;
	// Check file existence
	returnval = access (filepath, F_OK);
	if (returnval == 0)
	{
		printf ("\n %s exists\n", strvar);

	    fichier = fopen("E3A/s01n001.E34", "r");
	 
	    if (fichier != NULL)
	    {

	        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
	        printf("%s", chaine); // On affiche la chaîne 
	        fclose(fichier);
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
	}
	/**
	printf("YES");
    FILE* fichier = NULL;
    char chaine[TAILLE_MAX] = ""; // Chaîne vide de taille TAILLE_MAX
 	
 	filePath = "E3A/s01n001.E34";

 	returnval = access (filepath, F_OK);
	if (returnval == 0)
		printf (“\n %s exists\n”, strvar);
	else
	{
		if (errno == ENOENT)
			printf (“%s No such file or directory.\n”, filepath);

		else if (errno == EACCES)
			printf (“%s Permission denied.\n”, filepath);
	}

    fichier = fopen("E3A/s01n001.E34", "r");
 
    if (fichier != NULL)
    {

        fgets(chaine, TAILLE_MAX, fichier); // On lit maximum TAILLE_MAX caractères du fichier, on stocke le tout dans "chaine"
        printf("%s", chaine); // On affiche la chaîne 
        fclose(fichier);
    }
 	
 	else
    {
       // On affiche un message d'erreur si on veut
       printf("Impossible d'ouvrir le fichier test.txt");

    }
*/
    return 0;
}