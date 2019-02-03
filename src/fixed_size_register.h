#ifndef FIXED_SIZE_REGISTER_H
#define FIXED_SIZE_REGISTER_H

#include "data_file.h"

class FixedSizeRegister
{
private:
	DataFile *dataFile;
	int id;
	char *name;
	double salary;
	char *job;

public:
	FixedSizeRegister();
	~FixedSizeRegister();
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