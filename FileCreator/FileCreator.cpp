// FileCreator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataFile.h"
#include "FixedSizeRegister.h"
#include "KnowVarSizeRegister.h"

struct Item
{
	int id;
	char name[30];
};

char * serializeFixedSize(int id, char name[30], double salary, char job[20])
{
	char * data = new char[sizeof(int) + 30 + 20 + sizeof(salary)];

	memcpy(data, reinterpret_cast<char*>(&id), sizeof(int));

	memcpy(data + sizeof(id), name, 30);

	memcpy(data + sizeof(id) + 30, reinterpret_cast<char*>(&salary), sizeof(salary));

	memcpy(data + sizeof(id) + 30 + sizeof(salary), job, 20);

	return data;
}

char * serializeKnownVarSize(int id, char * name, double salary, char * job, int sizeName, int sizeJob)
{
	char * data = new char[sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary) + sizeof(sizeJob) + sizeJob];

	memcpy(data, reinterpret_cast<char*>(&id), sizeof(id));

	memcpy(data + sizeof(id), reinterpret_cast<char*>(&sizeName), sizeof(sizeName));

	memcpy(data + sizeof(id) + sizeof(sizeName), name, sizeName);

	memcpy(data + sizeof(id) + sizeof(sizeName) + sizeName, reinterpret_cast<char*>(&salary), sizeof(salary));

	memcpy(data + sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary), reinterpret_cast<char*>(&sizeJob), sizeof(sizeJob));

	memcpy(data + sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary) + sizeof(sizeJob), job, sizeJob);

	return data;
}

int main()
{
	// write tests

	/*string location = "products.bin";
	char path[30];
	strcpy_s(path, 30, location.c_str());

	DataFile *dataFile = new DataFile(path);

	Item item, *product = new Item();

	item.id = 1;

	strcpy_s(item.name, 30, (char*)"Product 1");

	dataFile->write(reinterpret_cast<char*>(&item), 0, sizeof(Item));

	product = reinterpret_cast<Item*>(dataFile->read(0, sizeof(Item)));

	cout << product->id << endl;
	cout << product->name << endl;
	dataFile->close();
	system("pause");*/

	// Register fixed Size tests

	//string personName = "Escalon", jobType = "QA";

	//char name[30];
	//char job[20];
	//unsigned int id = 1;
	//double salary = 2000;

	//strcpy_s(name, 30, personName.c_str());
	//strcpy_s(job, 20, jobType.c_str());

	//FixedSizeRegister * fileRegister = new FixedSizeRegister();
	//fileRegister->openFile((char*)"fixedSizeFieldFile.dat");

	//char * data = serializeFixedSize(id, name, salary, job);

	///*fileRegister->fromChar(data);
	//fileRegister->writeIntoFile();
	//fileRegister->closeFile();*/

	//fileRegister->openFile((char*)"fixedSizeFieldFile.dat");
	//fileRegister->readIntoFile(4);
	//fileRegister->printRegister();
	//fileRegister->closeFile();

	// Know Var Size Tests

	string personName = "Escalon", jobType = "QA";

	char name[] = "Escalon";
	char job[] = "QA";
	unsigned int id = 4;
	double salary = 2000;

	KnowVarSizeRegister * fileRegister = new KnowVarSizeRegister();
	fileRegister->openFile((char*)"knowVarSizeFieldFile.dat");

	char * data = serializeKnownVarSize(id, name, salary, job, sizeof(name), sizeof(job));

	/*fileRegister->fromChar(data);
	fileRegister->writeIntoFile();
	fileRegister->closeFile();*/

	fileRegister->openFile((char*)"knowVarSizeFieldFile.dat");

	fileRegister->readIntoFile(2);
	fileRegister->printRegister();

	/*fileRegister->readIntoFile(1);
	fileRegister->printRegister();

	fileRegister->readIntoFile(2);
	fileRegister->printRegister();*/

	fileRegister->closeFile();


	system("pause");

    return 0;
}

