#include <vector>
#include <algorithm>
#include "SortedIndex.h"

using namespace std;

//// actions ////
void SortedIndex::sort(vector<int> values)
{
  // fill:
  this->indexes.resize(values.size()); // resize indexes
  for(int i = 0; i < values.size(); i++) indexes[i] = i; // fill indexes {0, 1, 2...}

  // sort:
  std::sort(this->indexes.begin(), this->indexes.begin() + this-> indexes.size(), [&](int n0, int n1) {return(values[n0] < values[n1]);}); // sort indexes by values
}
void SortedIndex::invertedSort(vector<int> values)
{
  // fill:
  vector<int> indexes(values.size());
  for(int i = 0; i < values.size(); i++) indexes[i] = i; // fill indexes {0, 1, 2...}

  // sort:
  std::sort(indexes.begin(), indexes.begin() + indexes.size(), [&](int n0, int n1) {return(values[n0] < values[n1]);}); // sort indexes by values

  // invert:
  this->indexes.resize(values.size()); // resize indexes
  for(int i = 0; i < indexes.size(); i++) this->indexes[indexes[i]] = i; // invert indexes
}
void SortedIndex::sortData(char* &data, int length)
{
  // check:
  if(length != this->indexes.size())
    return; // TODO throw error here
  // variables:
  char* newData = new char[length];
  // sort:
  for(int i = 0; i < length; i++)
  {
    newData[i] = data[this->indexes[i]];
  }
  // return:
  delete[] data;
  data = newData;
}

//// accessors ////
int SortedIndex::findNext()
{
  for(int i = 0; i < indexes.size(); i++) // loop through indexes
  {
    if(indexes[i] != -1) // if index is not burnt
    {
      return(i);
    }
  }
  return(-1); // all indexes are burnt
}
