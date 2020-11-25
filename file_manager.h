/** 
	this method get all files names from de dirpath directory and store them to files arrays
	@param dirpath the directory path
	@param files the array to store all files name 
**/
void get_file_names(const char* dirpath, char** files);


/**
	this methode read a file by method name and store the content in struct object
	@param filepath the file path needed to read
	@param line where to store the readed line
	@param method the choosed method
	@param data, object to store data
**/
void read_file(char* filepath, char* line, char* method,struct object *data);