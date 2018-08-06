#include "stdafx.h"
#include "KnowVarSizeRegister.h"


KnowVarSizeRegister::KnowVarSizeRegister()
{
}


KnowVarSizeRegister::~KnowVarSizeRegister()
{
	delete[] this->name;
	delete[] this->job;
	delete this->dataFile;
}

void KnowVarSizeRegister::printRegister()
{
	cout << "Id: " << this->id << endl;
	cout << "Name: " << this->name << endl;
	cout << "Job: " << this->job << endl;
	cout << "Salary: " << this->salary << endl;
}

char * KnowVarSizeRegister::toChar()
{
	const int size = this->getSize();
	char * data = new char[size];

	memcpy(data, reinterpret_cast<char*>(&this->id), sizeof(this->id));

	memcpy(data + sizeof(this->id), reinterpret_cast<char*>(&this->sizeName), sizeof(this->sizeName));

	memcpy(data + sizeof(this->id) + sizeof(this->sizeName), this->name, this->sizeName);

	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, reinterpret_cast<char*>(&this->salary), sizeof(this->salary));

	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), reinterpret_cast<char*>(&this->sizeJob), sizeof(this->sizeJob));

	memcpy(data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->job, this->sizeJob);

	return data;
}

void KnowVarSizeRegister::fromChar(char * data)
{
	memcpy(&this->id, data, sizeof(this->id));
	
	memcpy(&this->sizeName, data + sizeof(this->id), sizeof(this->sizeName));
	this->name = new char[this->sizeName];

	memcpy(this->name, data + sizeof(this->id) + sizeof(this->sizeName), this->sizeName);
	
	memcpy(&this->salary, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, sizeof(this->salary));

	memcpy(&this->sizeJob, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(this->sizeJob));
	this->job = new char[this->sizeJob];

	memcpy(this->job, data + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);
}

void KnowVarSizeRegister::openFile(char * name)
{
	this->dataFile = new DataFile(name);
}

void KnowVarSizeRegister::writeIntoFile()
{
	this->dataFile->write(this->toChar(), this->getSize());
}

void KnowVarSizeRegister::readIntoFile(int position)
{
	int countSize = 0;



	for (int i = 0; i <= position; i++)
	{
		this->id = *(reinterpret_cast<int*>(this->dataFile->readKnownSize(countSize, sizeof(int))));
		this->sizeName = *(reinterpret_cast<int*>(this->dataFile->readKnownSize(countSize + sizeof(int), sizeof(int))));
		this->name = this->dataFile->readKnownSize(countSize + sizeof(this->id) + sizeof(this->sizeName), this->sizeName);
		this->salary = *(reinterpret_cast<double*>(this->dataFile->readKnownSize(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName, sizeof(double))));
		this->sizeJob = *(reinterpret_cast<int*>(this->dataFile->readKnownSize(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary), sizeof(int))));
		this->job = this->dataFile->readKnownSize(countSize + sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob), this->sizeJob);

		countSize += this->getSize();

	}
}

void KnowVarSizeRegister::closeFile()
{
	this->dataFile->close();
}

int KnowVarSizeRegister::getSize()
{
	return sizeof(this->id) + sizeof(this->sizeName) + this->sizeName + sizeof(this->salary) + sizeof(this->sizeJob) + this->sizeJob;
}
