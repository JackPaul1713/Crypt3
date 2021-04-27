#ifndef BLOCK_H
#define BLOCK_H

class Block
{
  private:
    // attributes
    const std::vector<std::vector<char*>> block; // data
    const int size; // x and y size
    bool full;
    // helpers:
    std::vector<char> getRow(int y);
    std::vector<char> getCol(int x);
    void setRow(int y, const std::vector<char> row);
    void setCol(int x, const std::vector<char> col);
    void swapRows(int y0, int y1);
    void swapCols(int x0, int x1);
  public:
    // constructors:
    Block() {} // default
    Block(char* bytes, int length, int pos, int size); // full
    Block(const Block& block); // copy
    // deconstructor:
    ~Block() {}
    // accessors:
    std::vector<std::vector<char*>> getBlock() {return(block);}
    int getSize() {return(size);}
    bool isFull() {return(full);}
    // mutators:
    void load(char* bytes, int length, int size);
    // helpers:
    friend void swap(Block& block0, Block& block1);
    // overloads:
    Block& operator=(Block block) {Block::swap(*this, block); return(*this);} // assignment
};

#endif
