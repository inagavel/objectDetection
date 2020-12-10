

int store_data(char* line,  struct object *data, char *method, int *i)
{
	if (strcmp(method, "E34") == 0) 
	{
	// printf("METHOD E34gdb --version");
	  data->e34[*i] = atof(line);
	} 
	else if (strcmp(method, "F0") == 0)
	{
	//	printf("METHOD  F0");
		data->f0[*i] = atof(line);
	}
	else if (strcmp(method, "GFD") == 0)
	{
	//	 printf("METHOD  GFD");
		data->gfd[*i] = atof(line);
	}
	else if (strcmp(method, "SA") == 0)
	{
	//	printf("METHOD SA");
		data->sa[*i] = atof(line);
	}
	/* more else if clauses */
	else /* default: */
	{
		printf("METHOD NOT FOUND");
	}

	return 0;
}

bool conatains(char* str1,char* str2)
{
		char * ptr;

		ptr = strstr(str1, str2);
    	if(ptr != NULL) // skip the . and .. files in Unix OS
    	{
    		return true;
    	}
    		
    	
	return false;
}
/** LES OBJETS D'entrainement  **/
int add_start_data(struct object *data,struct object *classifieddata, struct object *datatoclassify)
{
	char * ptr;
	int i = 0;
	int j = 0;
	int k = 0;
	while(i < CLASS_NUMBER*TRAINNING_NUMBER)
	{
		bool found = false;
    	if(conatains(data[i].name,"001") || conatains(data[i].name,"002") || conatains(data[i].name,"003")  ) // skip the . and .. files in Unix OS
    	{
			classifieddata[j] = data[i];
			j++;
		} 
		
		else 
		{
			datatoclassify[k] = data[i];
			k++;
		}	
		i++;
	} 

	
	
	return 0;
}
int init_class(struct class* allclass,struct object* data)
{
	char* class_array[]  = {"s01","s02","s03","s04","s05","s06","s07","s08","s09"};
	int i = 0;

	while(i < CLASS_NUMBER)
	{
		allclass[i].name = class_array[i];

		int j = 0;
		while( j < CLASS_NUMBER*TRAINNING_NUMBER)
		{
			allclass[i].element[j] = NULL;
			j++;
		}
		i++;
	}

	return 0;
}
int initialize_class(struct object *data,struct class *allclass, struct object *datatoclassify)
{
	char *c_tmp;
	int i = 0;
	int j = 0;
	int k = 0;
	int id=0;
	while(i < CLASS_NUMBER*TRAINNING_NUMBER)
	{
		bool found = false;
    	if(conatains(data[i].name,"001") || conatains(data[i].name,"002") || conatains(data[i].name,"003")  ) // skip the . and .. files in Unix OS
    	{
    		if (conatains(data[i].name,"s01")) 
			{
				c_tmp = "s01";
				id = 1;
			} 
			else if  (conatains(data[i].name,"s02")) 
			{
				c_tmp = "s02";
				id = 2;
			}
			else if(conatains(data[i].name,"s03")) 
			{
				c_tmp = "s03";
				id = 3;
			}
			else if (conatains(data[i].name,"s04")) 
			{
				c_tmp = "s04";
				id = 4;
			}
			else if(conatains(data[i].name,"s05")) 
			{
				c_tmp = "s05";
				id = 5;
				
			}
			else if (conatains(data[i].name,"s06")) 
			{
				c_tmp = "s06";
				id = 6;
			}
			else if (conatains(data[i].name,"s07")) 
			{
				c_tmp = "s07";
				id = 7;
				
			}
			else if (conatains(data[i].name,"s08")) 
			{
				c_tmp = "s08";
				id = 8;
			}
			else if (conatains(data[i].name,"s09")) 
			{
				c_tmp = "s09";
				id = 9;
			}
			/* more else if clauses */
			else /* default: */
			{
				printf("CLASS NOT FOUND");
			}

			if(c_tmp != NULL){
				
				int m = 0;
				bool ok = false;
				while(m < CLASS_NUMBER)
				{
					if(ok) break;
					if( allclass[m].name == c_tmp)
					{	
						int l = 0;
						while(l < CLASS_NUMBER*TRAINNING_NUMBER)
						{
							if(allclass[m].element[l] == NULL){
								
								allclass[m].element[l] = &data[i];
								allclass[m].id = id;
								//printf("m:%d,%d     c_tmp :%s  name :%s\n",m,l,c_tmp,allclass[m].element[l]->name );
								ok = true;
								break;
							}

							l++;
						}
					}

					m++;
				}
			}
			j++;
		} 
		// not 3ths elements
		else 
		{
			datatoclassify[k] = data[i];
			k++;
		}	
		i++;
	} 

	return 0;
}