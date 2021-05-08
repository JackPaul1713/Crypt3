#ifndef BLOCK_H
#define BLOCK_H

#include <vector>

class Block
{
  private:
    // attributes
    std::vector<std::vector<char*>> block; // data
    int size; // x and y size
    int length;
    bool full;
  public:
    // constructors:
    Block(): block(), size(0), length(0), full(false) {} // default
    Block(char* bytes, int length, int pos, int size); // full
    Block(const Block& block); // copy
    // deconstructor:
    ~Block() {}
    // accessors:
    std::vector<std::vector<char*>> getBlock() const {return(block);}
    int getSize() const {return(size);}
    int getLength() const {return(length);}
    bool isFull() const {return(full);}
    std::vector<char> getRow(int y) const;
    std::vector<char> getCol(int x) const;
    // mutators:
    void load(char* bytes, int length, int pos, int size);
    void setRow(int y, const std::vector<char> row);
    void setCol(int x, const std::vector<char> col);
    void swapRows(int y0, int y1);
    void swapCols(int x0, int x1);
    // helpers:
    friend void swap(Block& block0, Block& block1);
    friend void test();
    // overloads:
    Block& operator=(Block block) {swap(*this, block); return(*this);} // assignment
    friend bool operator==(const Block& block0, const Block& block1); // equality
    friend bool operator!=(const Block& block0, const Block& block1); // inequality
    // debuging:
    friend void test();
};

#endif
