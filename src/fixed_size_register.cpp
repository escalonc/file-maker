#include <cstring>
#include <iostream>
#include "fixed_size_register.h"

using namespace std;

FixedSizeRegister::FixedSizeRegister()
{
	this->name = new char[30];
	this->job = new char[20];
}

FixedSizeRegister::~FixedSizeRegister()
{
	delete[] this->name;
	delete[] this->job;
	delete this->dataFile;
}

void FixedSizeRegister::printRegister()
{
	cout << "Id: " << this->id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Job: " << this->job << endl;
	cout << "Salary: " << this->salary << endl;
}

char *FixedSizeRegister::toChar()
{
	const int size = this->getSize();
	char *data = new char[size];
	int position = 0;

	memcpy(&data[position], reinterpret_cast<char *>(&this->id), sizeof(this->id));
	position += sizeof(this->id);
	memcpy(&data[position], this->name, 30);
	position += 30;
	memcpy(&data[position], reinterpret_cast<char *>(&this->salary), sizeof(this->salary));
	position += sizeof(this->salary);
	memcpy(&data[position], this->job, 20);

	return data;
}

void FixedSizeRegister::fromChar(char *data)
{
	int postion = 0;
	memcpy(&this->id, &data[postion], sizeof(this->id));
	postion += sizeof(this->id);
	memcpy(this->name, &data[postion], 30);
	postion += 30;
	memcpy(&this->salary, &data[postion], sizeof(this->salary));
	postion += sizeof(this->salary);
	memcpy(this->job, &data[postion], 20);
}

void FixedSizeRegister::openFile(char *name)
{
	this->dataFile = new DataFile(name);
}

void FixedSizeRegister::writeIntoFile()
{
	this->dataFile->open(std::ios::in | std::ios::out | std::ios::binary | std::ios::app);
	this->dataFile->write(this->toChar(), this->getSize());
	this->dataFile->close();
}

void FixedSizeRegister::readIntoFile(int position)
{
	this->dataFile->open();
	char *data = this->dataFile->read(position, this->getSize());
	this->fromChar(data);
	this->dataFile->close();
	delete data;
}

void FixedSizeRegister::closeFile()
{
	this->dataFile->close();
}

int FixedSizeRegister::getSize()
{
	return sizeof(this->id) + 30 + 20 + sizeof(this->salary);
}
