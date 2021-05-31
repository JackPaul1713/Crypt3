#include <vector>
#include <iostream> // DEBUG
#include "Block.h"

using namespace std;

//// constructors ////
Block::Block(char* bytes, int length, int pos, int size): // full
block(), size(size), length(0), full(false)
{
  load(bytes, length, pos, size);
}
Block::Block(const Block& block): // copy
block(block.block), size(block.size), length(block.length), full(block.full)
{}

//// accessors ////
vector<char> Block::getRow(int y) const
{
  vector<char> row(size);
  for(int x = 0; x < size; x++) // loop through block[y]
  {
    row.at(x) = *block.at(y).at(x); // set row to x values
  }
  return(row);
}
vector<char> Block::getCol(int x) const
{
  vector<char> col(size);
  for(int y = 0; y < size; y++) // loop through block
  {
    col.at(y) = *block.at(y).at(x); // set row to y values
  }
  return(col);
}

//// mutators ////
void Block::load(char* bytes, int length, int pos, int size)
{
  // cout << "Block::load(bytes: *bytes*, length: " << length << ", pos: " << pos << ", size: " << size << ")\n"; // DEBUG
  // set attributes:
  this->size = size; // attribute: size
  block.resize(size); // attribute: block y size
  for(int y = 0; y < size; y++) // loop through block
  {
    block.at(y) = vector<char*>(size); // attribute: block x size
    // cout << "  "; // DEBUG
    for(int x = 0; x < size; x++) // loop through block[y]
    {
      if(pos < length) // wrap pos arround
      {
        block.at(y).at(x) = &bytes[pos]; // attribute: block[y][x]
        // cout << "[" << y << "," << x << "]:" << *block[y][x] << " "; // DEBUG
        this->length++; // increment length of block
        pos++; // increment pos
      }
      else
      {
        // cout << endl; // DEBUG
        return;
      }
    }
    // cout << endl; // DEBUG
  }
  full = true; // attribute: full
}

void Block::setRow(int y, const vector<char> row)
{
  for(int x = 0; x < size; x++) // loop through block[y]
  {
    *block.at(y).at(x) = row.at(x); // set x values
  }
}
void Block::setCol(int x, const vector<char> col)
{
  for(int y = 0; y < size; y++)
  {
    *block.at(y).at(x) = col.at(x); // set y values
  }
}
void Block::swapRows(int y0, int y1)
{
  for(int x = 0; x < size; x++)
  {
    swap(*block.at(y0).at(x), *block.at(y1).at(x));
  }
}
void Block::swapCols(int x0, int x1)
{
  for(int y = 0; y < size; y++)
  {
    swap(*block.at(y).at(x0), *block.at(y).at(x1));
  }
}

//// helpers ////
void swap(Block& block0, Block& block1)
{
  // swap all attributes between objects:
  swap(block0.block, block1.block);
  swap(block0.size, block1.size);
  swap(block0.full, block1.full);
}

//// operators ////
bool operator==(const Block& block0, const Block& block1)
{
  // variables:
  bool blocksEqual = true;
  int length = 0;
  // check size and length:
  if((block0.size != block1.size) || (block0.length != block1.length)) // if differnt sizes or lengths
  {
    return(false);
  }
  // check values:
  for(int y = 0; y < block0.block.size(); y++) // loop through block
  {
    for(int x = 0; x < block0.block.size(); x++) // loop through block[y]
    {
      if(length >= block0.length) // if length is used up
      {
        break;
      }
      if(block0.block.at(y).at(x) != block1.block.at(y).at(x)) // if differnt values
      {
        blocksEqual = false;
      }
      length++; // iterate length
    }
  }
  if((!blocksEqual) || (block0.size != block1.size) || (block0.length != block1.length) || (block0.full != block1.full))
  {
    return(false);
  }
  return(true);
}
bool operator!=(const Block& block0, const Block& block1)
{
  return(!(block0 == block1));
}
