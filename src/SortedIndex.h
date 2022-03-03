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
    void sort(std::vector<int> values);
    void invertedSort(std::vector<int> values); // sorted indexs switched with their indexs
    void sortData(char* &data, int length); // sorts data by the sorted index
    // accessors:
    std::vector<int> indexez() {return(indexes);}
    int at(int i) {return(indexes.at(i));}
    int findNext();
    int size() {return(indexes.size());}
    // mutators:
    void burn(int i) {indexes[i] = -1;}
    void push_back(int i) {indexes.push_back(i);}
    // friends:
    friend void swap(SortedIndex& sortedIndex0, SortedIndex& sortedIndex1) {swap(sortedIndex0.indexes, sortedIndex1.indexes);}
    friend void debug();
    // overloads:
    SortedIndex& operator=(SortedIndex sortedIndex) {swap(*this, sortedIndex); return(*this);} // assignment
    int& operator[](int i) {return(indexes[i]);} // accessor
};

#endif
