#include <iostream>
#include "Cypher.h"
#include "Key.h"
#include "SortedIndex.h"
#include "random.h"

using namespace std;

static bool init = (srand(time(0)), true); // seed rand

char* generateData(int length) // generates random data
{
  char* data = new char[length];
  for(int i = 0; i < length; i++) // fill data
  {
    data[i] = rand() % 256; // generate random character
  }
  return(data);
}

void debug()
{
  // variables:
  Cypher cypher(Key(16));
  char* data = generateData(28);

  // action:
  cypher.encryptPos(data, 28);
  delete[] data;
}

int main()
{
  debug();
}
