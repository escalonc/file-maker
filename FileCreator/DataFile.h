#pragma once

#include <fstream>

class DataFile
{
private:
	fstream * file;
	char * path;
public:
	DataFile();
	DataFile(char * path);
	void open();
	void close();
	void write(char * data, unsigned int position, unsigned int size);
	char* read(unsigned int position, unsigned int size);
};

