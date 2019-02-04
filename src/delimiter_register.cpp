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
}

int DelimiterRegister::getSize()
{
  return sizeof(this->id) + strlen(this->name) + sizeof(this->salary) + strlen(this->job) + 1 + 3;
}