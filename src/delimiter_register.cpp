#include <cstring>
#include "delimiter_register.h"

#include <string>

using namespace std;

DelimiterRegister::DelimiterRegister()
{
  this->dataFile = new DataFile((char *)"delimiter_file.dat");
}

DelimiterRegister::~DelimiterRegister()
{
  delete this->dataFile;
}

void DelimiterRegister::writeIntoFile()
{

  if (this->dataFile->isEmpty())
  {
    this->dataFile->write((char *)"|", sizeof(char));
  }

  this->dataFile->write(this->toChar(), this->getSize());
}
char *DelimiterRegister::toChar()
{
  char recordDelimiter = '|';
  char fieldDelimiter = ';';
  char *data = new char[this->getSize()];

  memcpy(data, reinterpret_cast<char *>(&this->id), sizeof(int));
  data += sizeof(int);
  memcpy(data, &fieldDelimiter, sizeof(char));
  data += sizeof(char);
  memcpy(data, reinterpret_cast<char *>(this->name), strlen(this->name));
  data += strlen(this->name);
  memcpy(data, &fieldDelimiter, sizeof(char));
  data += sizeof(char);
  memcpy(data, reinterpret_cast<char *>(&this->salary), sizeof(double));
  data += sizeof(double);
  memcpy(data, &fieldDelimiter, sizeof(char));
  data += sizeof(char);
  memcpy(data, reinterpret_cast<char *>(this->job), strlen(this->job));
  data += strlen(this->job);
  memcpy(data, &recordDelimiter, sizeof(char));

  return data;
}

void DelimiterRegister::fromChar(char *data)
{
  char recordDelimiter = '|';
  char fieldDelimiter = ';';

  int position = 0;

  char *token = strtok(data, &fieldDelimiter);
  int length = strlen(token);

  memcpy(&this->id, &data[position], sizeof(int));
  position += sizeof(int) + 1;

  token = strtok(nullptr, &fieldDelimiter);
  length = strlen(token);

  memcpy(this->name, &data[position], length);
  position += length + 1;

  token = strtok(nullptr, &fieldDelimiter);

  memcpy(&this->salary, &data[position], sizeof(double));
  position += sizeof(double) + 1;

  token = strtok(nullptr, &recordDelimiter);
  length = strlen(token);
  memcpy(this->job, &data[position], length);
}

int DelimiterRegister::getSize()
{
  return sizeof(this->id) + strlen(this->name) + sizeof(this->salary) + strlen(this->job) + 1 + 3;
}