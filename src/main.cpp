#include <cstring>
#include <iostream>
#include "data_file.h"
#include "fixed_size_register.h"
#include "known_variable_size_register.h"

using namespace std;

struct Item
{
	int id;
	char name[30];
};

char *serializeFixedSize(int id, char name[30], double salary, char job[20])
{
	char *data = new char[sizeof(int) + 30 + 20 + sizeof(salary)];

	memcpy(data, reinterpret_cast<char *>(&id), sizeof(int));
	data += sizeof(int);
	memcpy(data, name, 30);
	data += 30;
	memcpy(data, reinterpret_cast<char *>(&salary), sizeof(salary));
	data += sizeof(salary);
	memcpy(data, job, 20);

	return data;
}

char *serializeKnownVarSize(int id, char *name, double salary, char *job, int sizeName, int sizeJob)
{
	char *data = new char[sizeof(id) + sizeof(sizeName) + sizeName + sizeof(salary) + sizeof(sizeJob) + sizeJob];

	memcpy(data, reinterpret_cast<char *>(&id), sizeof(id));
	data += +sizeof(id);
	memcpy(data, reinterpret_cast<char *>(&sizeName), sizeof(sizeName));
	data += sizeof(sizeName);
	memcpy(data, name, sizeName);
	data += sizeName;
	memcpy(data, reinterpret_cast<char *>(&salary), sizeof(salary));
	data += sizeof(salary);
	memcpy(data, reinterpret_cast<char *>(&sizeJob), sizeof(sizeJob));
	data += sizeof(sizeJob);
	memcpy(data, job, sizeJob);

	return data;
}

int main()
{
	int option;
	char continueInput = 's';

	while (continueInput == 's')
	{
		cout << "********************************" << endl;
		cout << "*  1) Escribir fixed size file *" << endl;
		cout << "*  2) Leer fixed size file     *" << endl;
		cout << "*  3) Escribir known size file *" << endl;
		cout << "*  4) Leer known size file     *" << endl;
		cout << "*  5) Escribir delimiter file  *" << endl;
		cout << "*  6) Leer delimiter file      *" << endl;
		cout << "********************************" << endl;

		cout << "Ingrese una opción:" << endl;

		cin >> option;

		FixedSizeRegister *fixedRegister = new FixedSizeRegister();
		KnowVariableSizeRegister *knownSizeRegister = new KnowVariableSizeRegister();

		switch (option)
		{
		case 1:

		{
			char fixedName[30], fixedJob[20];
			int fixedId;
			double fixedSalary;

			fixedRegister->openFile((char *)"fixedSizeFieldFile.dat");

			cout << "Ingrese el id: " << endl;
			cin >> fixedId;

			cout << "Ingrese el nombre: " << endl;
			cin >> fixedName;

			cout << "Ingrese el trabajo: " << endl;
			cin >> fixedJob;

			cout << "Ingrese el salario: " << endl;
			cin >> fixedSalary;

			char *data = serializeFixedSize(fixedId, fixedName, fixedSalary, fixedJob);

			fixedRegister->fromChar(data);
			fixedRegister->writeIntoFile();
			fixedRegister->closeFile();
		}

		break;

		case 2:

		{
			int fixedPosition;
			cout << "Ingrese la posición: " << endl;
			cin >> fixedPosition;

			fixedRegister->openFile((char *)"fixedSizeFieldFile.dat");

			fixedRegister->readIntoFile(fixedPosition);
			fixedRegister->printRegister();
			fixedRegister->closeFile();
		}

		break;

		case 3:

		{
			char knownSizeName[30], knownSizeJob[20];
			int knownSizeId;
			double knownSizeSalary;

			knownSizeRegister->openFile((char *)"knownSizeFieldFile.dat");

			cout << "Ingrese el id: " << endl;
			cin >> knownSizeId;

			cout << "Ingrese el nombre: " << endl;
			cin >> knownSizeName;

			cout << "Ingrese el trabajo: " << endl;
			cin >> knownSizeJob;

			cout << "Ingrese el salario: " << endl;
			cin >> knownSizeSalary;

			char *data = serializeKnownVarSize(knownSizeId, knownSizeName, knownSizeSalary, knownSizeJob, sizeof(knownSizeName), sizeof(knownSizeJob));

			knownSizeRegister->fromChar(data);
			knownSizeRegister->writeIntoFile();
		}

		break;
		case 4:

		{
			int knownSizePosition;
			cout << "Ingrese la posición: " << endl;
			cin >> knownSizePosition;

			knownSizeRegister->openFile((char *)"knownSizeFieldFile.dat");

			knownSizeRegister->readIntoFile(knownSizePosition);
			knownSizeRegister->printRegister();
		}

		break;
		case 5:
		{
			char name[30], job[20];
			int id;
			double salary;

			fixedRegister->openFile((char *)"delimiter_file.dat");

			cout << "Ingrese el id: " << endl;
			cin >> id;

			cout << "Ingrese el nombre: " << endl;
			cin >> name;

			cout << "Ingrese el trabajo: " << endl;
			cin >> job;

			cout << "Ingrese el salario: " << endl;
			cin >> salary;

			char *data = serializeFixedSize(id, name, salary, job);

			fixedRegister->fromChar(data);
			fixedRegister->writeIntoFile();
			fixedRegister->closeFile();
		}

		break;
		case 6:

			break;
		}

		cout << "¿Desea continuar, ingrese 's' para continuar? " << endl;
		cin >> continueInput;
	}

	return 0;
}
