#ifndef SORTEDINDEX_H
#define SORTEDINDEX_H

#include <vector>
#include <string>

class SortedIndex // indexs of a vector sorted by the vectors values
{
  private:
    // attributes:
    std::vector<int> indexes;
  public:
    // constructors:
    SortedIndex() {} // default
    SortedIndex(std::vector<int> indexes): indexes(indexes) {} // vector
    SortedIndex(const SortedIndex& sortedIndex): indexes(sortedIndex.indexes) {} // copy
    // deconstructor:
    ~SortedIndex() {}
    // actions:
    void sort(std::vector<int> values); // sorts indexes by values
    void invertedSort(std::vector<int> values); // sorts indexes by values and inverts indexes
    void sortData(char* &data, int length); // sorts data by the sorted index
    // accessors:
    int at(int i) {return(indexes.at(i));}
    int size() {return(indexes.size());}
    // friends:
    friend void swap(SortedIndex& sortedIndex0, SortedIndex& sortedIndex1) {swap(sortedIndex0.indexes, sortedIndex1.indexes);}
    friend void debug(); // DEBUG
    // overloads:
    SortedIndex& operator=(SortedIndex sortedIndex) {swap(*this, sortedIndex); return(*this);} // assignment
    int& operator[](int i) {return(indexes[i]);} // accessor
};

#endif
