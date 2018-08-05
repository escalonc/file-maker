#include "stdafx.h"
#include "DataFile.h"

DataFile::DataFile()
{
	this->file = new fstream();
}

DataFile::DataFile(char * path)
{
	this->path = path;

	this->file = new fstream();
	this->file->open(this->path, ios::in | ios::out | ios::trunc | ios::binary);
}

void DataFile::open()
{
	this->file->open(this->path, ios::in | ios::out | ios::binary);
}

void DataFile::close()
{
	this->file->close();
}

void DataFile::write(char * data, unsigned int position, unsigned int size)
{
	this->file->seekp(0, ios::beg);
	this->file->seekp(position * size);

	this->file->write(data, size);
}

char * DataFile::read(unsigned int position, unsigned int size)
{
	char* element = new char();

	this->file->seekg(0, ios::beg);
	this->file->seekg(position * size);

	this->file->read(element, size);

	return element;
}