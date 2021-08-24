#include <vector>
#include <string>
#include <iostream>
#include "SortedIndex.h"

using namespace std;

//// declarations ////
void compairSortedIndex(SortedIndex sortedIndex0, SortedIndex sortedIndex1);
void displaySortedIndex(SortedIndex sortedIndex, string name="sorted index");

//// testing ////
int main()
{
  cout << "TESTING SORTEDINDEX" << endl;
  {
    vector<int> values{15, 12, 17, 1};
    SortedIndex sortedIndex;
    sortedIndex.sort(values);
    displaySortedIndex(sortedIndex);
    sortedIndex.invertedSort(values);
    displaySortedIndex(sortedIndex, "inverted sorted index");
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
  cout << "    to:   ";
  for(int i = 0; i < sortedIndex.size(); i++)
  {
    cout << sortedIndex[i];
    if(sortedIndex[i] < 10) cout << "   ";
    else if(sortedIndex[i] < 100) cout << "  ";
    else if(sortedIndex[i] < 1000) cout << " ";
  }
  cout << "\n    from: ";
  for(int i = 0; i < sortedIndex.size(); i++)
  {
    cout << i;
    if(sortedIndex[i] < 10) cout << "   ";
    else if(sortedIndex[i] < 100) cout << "  ";
    else if(sortedIndex[i] < 1000) cout << " ";
  }
  cout << endl;
}
