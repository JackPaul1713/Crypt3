#include <iostream>
#include "SortedIndex.h"

using namespace std;

static bool init = (srand(time(0)), true); // seed rand

vector<int> generateValues(int length) // generates random data
{
  vector<int> data;
  for(int i = 0; i < length; i++) // fill data
  {
    data.push_back(rand() % 256); // generate random character
  }
  return(data);
}

void debug()
{
  cout << "Debug Sorted Index: " << endl;

  // variables:
  vector<int> values = generateValues(8);
  SortedIndex sortedIndex(values);

  // action:
  sortedIndex.sort(values);
  cout << "  values:" << endl << "    ";
  for(int i = 0; i < 8; i++) {cout << values[i] << " ";}
  cout << endl;
  
  cout << "  indexes:" << endl << "    ";
  for(int i = 0; i < 8; i++) {cout << sortedIndex.indexes[i] << " ";}
  cout << endl;

  sortedIndex.invertedSort(values);
  cout << "  inverted indexes:" << endl << "    ";
  for(int i = 0; i < 8; i++) {cout << sortedIndex.indexes[i] << " ";}
  cout << endl;
}

int main()
{
  debug();
}
