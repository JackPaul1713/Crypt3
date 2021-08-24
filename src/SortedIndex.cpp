#include <vector>
#include "SortedIndex.h"

using namespace std;

//// actions ////
void SortedIndex::sort(vector<int> values)
{
  // variables:
  vector<int> indexes(values.size()); for(int i = 0; i < values.size(); i++) indexes[i] = i;
  int min = 0; // minimum index
  // sort:
  while(values.size() > 0) // while values has data
  {
    // find minimum:
    for(int i = 0; i < values.size(); i++) // loop through values
    {
      if(values[i] < values[min]) // if current value is less than minimum value
      {
        min = i; // set new minimum
      }
    }
    this->indexes.push_back(indexes[min]); // add minimum index to current index of this indexes
    values.erase(values.begin() + min); // remove previous minimum value
    indexes.erase(indexes.begin() + min); // remove previous minimum index
    min = 0; // reset minimum index
  }
}
void SortedIndex::invertedSort(vector<int> values)
{
  // variables:
  vector<int> indexes(values.size()); for(int i = 0; i < values.size(); i++) indexes[i] = i;
  int min = 0; // minimum index
  int cur = 0; // current index
  // sort:
  while(values.size() > 0) // while values has data
  {
    // find minimum:
    for(int i = 0; i < values.size(); i++) // loop through values
    {
      if(values[i] < values[min]) // if current value is less than minimum value
      {
        min = i; // set new minimum
      }
    }
    // set:
    this->indexes[indexes[min]] = cur; // add current index to minimum index of this indexes
    values.erase(values.begin() + min); // remove previous minimum value
    indexes.erase(indexes.begin() + min); // remove previous minimum index
    min = 0; // reset minimum index
    cur++; // increment current index
  }
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
