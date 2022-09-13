#include <vector>
#include <string>
#include <iostream>
#include "../src/SortedIndex.h"

using namespace std;

//// declarations ////
void compairSortedIndex(SortedIndex sortedIndex0, SortedIndex sortedIndex1);
void displaySortedIndex(SortedIndex sortedIndex, string name="sorted index");

//// testing ////
int main()
{
  cout << "SORTEDINDEX TEST" << endl;
  {
    vector<int> values{15, 12, 17, 1};
    char* data = new char[4];
    data[0] = 'a';
    data[1] = 'b';
    data[2] = 'c';
    data[3] = 'd';
    SortedIndex sortedIndex;
    cout << "  values: ";
    for(int i = 0; i < values.size(); i++) cout << values[i] << " ";
    cout << endl;
    sortedIndex.sort(values);
    displaySortedIndex(sortedIndex);
    sortedIndex.sortData(data, 4);
    cout << "sortedData: " << data << endl;
    sortedIndex.invertedSort(values);
    displaySortedIndex(sortedIndex, "inverted sorted index");
    sortedIndex.sortData(data, 4);
    cout << "data: " << data << endl;
    delete[] data;
  }

  return(0);
}

//// definitions ////
void compairSortedIndex(SortedIndex sortedIndex0, vector<int> indexes)
{

}
void displaySortedIndex(SortedIndex sortedIndex, string name)
{
  cout << "  " << name << ": " << endl;
  cout << "    from: ";
  for(int i = 0; i < sortedIndex.size(); i++)
  {
    cout << sortedIndex[i];
    if(sortedIndex[i] < 10) cout << "   ";
    else if(sortedIndex[i] < 100) cout << "  ";
    else if(sortedIndex[i] < 1000) cout << " ";
  }
  cout << "\n    to:   ";
  for(int i = 0; i < sortedIndex.size(); i++)
  {
    cout << i;
    if(sortedIndex[i] < 10) cout << "   ";
    else if(sortedIndex[i] < 100) cout << "  ";
    else if(sortedIndex[i] < 1000) cout << " ";
  }
  cout << endl;
}
