#include <stdio.h>
#include <string.h>
#include "header.h"
#define E34_MAX  16 
#include <stdio.h>
#include <string.h>

float euclidean_distance(float coord_classified[], float coord_to_be_classified[], int MAX)
{
	float c_c;
	float c_t;
	
	float val = 0;
	int j = 0;
	while (j < MAX )
	{
		val += pow(coord_classified[j] - coord_to_be_classified[j],2);
		j++;
	}
	return sqrt(val);
}

int compare(struct  class_distance* cd1,struct class_distance* cd2)
{

	const struct  class_distance* c1 = (const struct  class_distance*)cd1;
   	const struct  class_distance* c2 = (const struct  class_distance*)cd2;

   	 if (c1->distance < c2->distance)
      return -1;
   else if (c1->distance > c2->distance)
      return 1;
   else
      return 0;
}

int classify(struct class_distance* c_d, int K)
{
	int i = 0;
	int class_occur[9]={0,0,0,0,0,0,0,0,0}; 
	int score[9]={0,0,0,0,0,0,0,0,0}; 
	while(i < K)
	{
		class_occur[c_d[i].id-1]++;
		score[c_d[i].id-1]+=K-i;
		i++;
	}
	int index=0;
	int majority = 0;
	int count = 0;
	i=0;
	while(i < CLASS_NUMBER)
	{	
		if(class_occur[i] > majority)
		{
			index =i;
			majority = class_occur[i];
		}
		else if(class_occur[i] == majority)
		{
			if(score[i]> score[index])
			{
				index =i;
				majority = class_occur[i];
			}
		}

		i++;
	}
	index++;

	return index;
}
