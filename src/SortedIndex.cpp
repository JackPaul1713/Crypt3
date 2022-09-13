#include <vector>
#include <algorithm>
/* DEBUG */ #include <iostream>
#include "SortedIndex.h"

using namespace std;

//// actions ////
void SortedIndex::sort(vector<int> values)  // sorts indexes by values
{
  // resize:
  this->indexes.resize(values.size()); // resize indexes
  // fill:
  for(int i = 0; i < values.size(); i++) indexes[i] = i; // fill indexes {0, 1, 2...}
  // sort:
  std::sort(this->indexes.begin(), this->indexes.begin() + this-> indexes.size(), [&](int n0, int n1) {return(values[n0] < values[n1]);}); // sort indexes by values
}
void SortedIndex::invertedSort(vector<int> values) // sorts indexes by values and inverts indexes
{
  // variables:
  vector<int> indexes(values.size());
  // fill:
  for(int i = 0; i < values.size(); i++) indexes[i] = i; // fill indexes {0, 1, 2...}
  // sort:
  std::sort(indexes.begin(), indexes.begin() + indexes.size(), [&](int n0, int n1) {return(values[n0] < values[n1]);}); // sort indexes by values
  // invert:
  this->indexes.resize(values.size()); // resize indexes
  for(int i = 0; i < indexes.size(); i++) this->indexes[indexes[i]] = i; // invert indexes
}
void SortedIndex::sortData(char* &data, int length) // sorts data by the sorted index, TODO throw error
{
  // check:
  if(length != this->indexes.size())
    return; // TODO throw error here
  // variables:
  char* newData = new char[length];
  // sort:
  for(int i = 0; i < length; i++) // loop through data
  {
    newData[i] = data[this->indexes[i]]; // sort data into new data
  }
  // return:
  delete[] data; // delete data
  data = newData; // replace data pointer with new data pointer
}
