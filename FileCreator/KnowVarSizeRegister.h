#pragma once
#include "DataFile.h"

class KnowVarSizeRegister
{
private:
	DataFile * dataFile;
	int id;
	int sizeName;
	char * name;
	double salary;
	int sizeJob;
	char * job;

public:
	KnowVarSizeRegister();
	~KnowVarSizeRegister();

	void printRegister();
	char* toChar();
	void fromChar(char* data);
	void openFile(char* name);
	void writeIntoFile();
	void readIntoFile(int position);
	void closeFile();
	int getSize();
};

