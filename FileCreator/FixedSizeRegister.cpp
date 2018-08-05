#include "stdafx.h"
#include "FixedSizeRegister.h"

FixedSizeRegister::FixedSizeRegister()
{
	this->dataFile = new DataFile((char*)"fixedSizeFile");
	this->name = new char[30];
	this->job = new char[20];
}

void FixedSizeRegister::printRegister()
{
}

char * FixedSizeRegister::toChar()
{
	char * data = new char[sizeof(int) + 30 + 20 + sizeof(salary)];

	memcpy(data, reinterpret_cast<char*>(&id), sizeof(int));

	memcpy(data + sizeof(id), name, 30);

	memcpy(data + sizeof(id) + 30, reinterpret_cast<char*>(&salary), sizeof(salary));

	memcpy(data + sizeof(id) + 30 + sizeof(salary), job, 20);

	return data;
}

void FixedSizeRegister::fromChar(char * data)
{
	memcpy(&this->id, data, sizeof(this->id));

	memcpy(this->name, data + sizeof(this->id), 30);

	memcpy(reinterpret_cast<char*>(&salary), data + sizeof(this->id) + 30, sizeof(this->salary));

	memcpy(job, data + sizeof(this->id) + 30 + sizeof(this->salary), 20);
}

void FixedSizeRegister::openFile(char * name)
{
}

void FixedSizeRegister::writeIntoFile()
{
}

void FixedSizeRegister::readIntoFile(int position)
{
}

void FixedSizeRegister::closeFile()
{
}

int FixedSizeRegister::getSize()
{
	return sizeof(this->id) + sizeof(this->name) + sizeof(this->job) + +sizeof(this->salary);
}
