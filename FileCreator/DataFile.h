#pragma once

#include <fstream>

class DataFile
{
private:
	fstream * file;
	char * path;
public:
	DataFile();
	~DataFile();
	DataFile(char * path);
	DataFile(char * path, ios_base::openmode mode);
	void open();
	void close();
	void write(char * data, unsigned int position, unsigned int size);
	void write(char * data, unsigned int size);
	char* read(unsigned int position, unsigned int size);
	char* readKnownSize(unsigned int position, unsigned int size);
};

