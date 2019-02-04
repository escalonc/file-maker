#ifndef KNOWN_VARIABLE_SIZE_REGISTER_H
#define KNOWN_VARIABLE_SIZE_REGISTER_H

#include "data_file.h"

class KnowVariableSizeRegister
{
private:
	DataFile *dataFile;
	int id;
	int sizeName;
	char *name;
	double salary;
	int sizeJob;
	char *job;

public:
	KnowVariableSizeRegister();
	~KnowVariableSizeRegister();

	void printRegister();
	char *toChar();
	void fromChar(char *data);
	void openFile(char *name);
	void writeIntoFile();
	void readIntoFile(int position);
	void closeFile();
	int getSize();
};

#endif