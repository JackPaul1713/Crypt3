#include <iostream>
#include <vector>
#include "Block.h"

using namespace std;

//// declarations ////
// compare:
void compareBlocks(string description, Block actual, Block expected);
void compareCharacters(string description, char* actual, char* expected);
// operators:
ostream& operator<<(ostream& os, const vector<vector<char*>>& block); // insertion
bool operator==(const vector<vector<char*>>& block0, const vector<vector<char*>>& block1); // equality
bool operator!=(const vector<vector<char*>>& block0, const vector<vector<char*>>& block1); // inequality

//// test ////
void test()
{
  // title:
  cout << "BLOCK TESTING" << endl;
  cout << endl;

  //// constructors ////
  cout << "Testing Constructors..." << endl;
  // default constructor:
  {
    // test:
    string name = "default constructor";
    Block actual;
    // expected:
    Block expected;
    expected.size = 0;
    expected.length = 0;
    expected.full = false;
    // check:
    compareBlocks(name, actual, expected);
  }
  // full constructor:
  {
    // test:
    string name = "full constructor";
    int size = 4;
    int pos = 0;
    int length = 16;
    char* characters = new char[length];
    for(int i = 0; i < length; i++) characters[i] = 'a' + i;
    Block actual(characters, length, pos, size);
    // expected:
    Block expected;
    vector<vector<char*>> block(size);
    int len = 0;
    for(int y = 0; y < size; y++)
    {
      block.at(y) = vector<char*>(size);
      for(int x = 0; x < size; x++) block.at(y).at(x) = &characters[(y * size) + x];
    }
    expected.block = block;
    expected.size = 4;
    expected.length = 16;
    expected.full = true;
    // check:
    compareBlocks(name, actual, expected);
    // cleanup:
    delete[] characters;
  }
  // full constructor (not full):
  {

  }
  // copy constructor:
  {

  }
  cout << "tests complete" << endl << endl;

  //// destructor ////
  cout << "Testing Destructor..." << endl;
  cout << "tests complete" << endl << endl;

  //// accessors ////
  cout << "Testing Accessors..." << endl;
  cout << "tests complete" << endl << endl;

  //// mutators ////
  cout << "Testing Mutators..." << endl;
  cout << "tests complete" << endl << endl;

  //// helpers ////
  cout << "Testing Helpers..." << endl;
  cout << "tests complete" << endl << endl;

  //// overloads ////
  cout << "Testing Overloads..." << endl;
  cout << "tests complete" << endl << endl;
}

int main()
{
  test();
  return(1);
}

//// definitions ////
// compare:
void compareBlocks(string description, Block actual, Block expected)
{
  if(actual != expected)
  {
    cout << "ERROR " << description << "," << endl;
    if(actual.getBlock() != expected.getBlock())
    {
      cout << ".block" << endl;
      cout << "actual: " << endl;
      cout << actual.getBlock() << endl;
      cout << "expected: " << endl;
      cout << expected.getBlock() << endl;
    }
    if(actual.getSize() != expected.getSize())
    {
      cout << ".size" << endl;
      cout << "actual: " << actual.getSize() << ", expected: " << expected.getSize() << endl;
    }
    if(actual.getLength() != expected.getLength())
    {
      cout << ".length" << endl;
      cout << "actual: " << actual.getLength() << ", expected: " << expected.getLength() << endl;
    }
    if(actual.isFull() != expected.isFull())
    {
      cout << ".full" << endl;
      cout << "actual: " << actual.isFull() << ", expected: " << expected.isFull() << endl;
    }
  }
}
void compareCharacters(string name, char* actual, char* expected)
{

}
// operators:
ostream& operator<<(ostream& os, const vector<vector<char*>>& block)
{
  for(int y = 0; y < block.size(); y++)
  {
    cout << "  ";
    for(int x = 0; x < block.size(); x++)
    {
      os << block.at(y).at(x) << " ";
    }
    if(y != block.size()-1) os << endl;
  }
  return(os);
}
bool operator==(const vector<vector<char*>>& block0, const vector<vector<char*>>& block1)
{
  if((block0.size() != block1.size()) || ((block0.size() > 0) && (block0.at(0).size() != block1.at(0).size()))) // if size is not equal
  {
    return(false);
  }
  for(int y = 0; y < block0.size(); y++)
  {
    for(int x = 0; x < block0.size(); x++)
    {
      if(block0.at(y).at(x) != block1.at(y).at(x))
      {
        return(false);
      }
    }
  }
  return(true);
}
bool operator!=(const vector<vector<char*>>& block0, const vector<vector<char*>>& block1)
{
  return(!(block0 == block1));
}
