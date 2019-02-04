#include "data_file.h"

class DelimiterRegister
{
private:
  DataFile *dataFile;

  int id;
  char *name;
  double salary;
  char *job;

public:
  DelimiterRegister();
  ~DelimiterRegister();

  void printRegister();
  char *toChar();
  void fromChar(char *data);
  void readFromFile(int position);
  void writeIntoFile();
  int getSize();
};
