#include <iostream>
#include "Block.h"

using namespace std;

void dispCharacters(char* characters, int length)
{
  cout << "characters:" << endl;
  for(int i = 0; i < length; i++)
  {
    cout << characters[i] << " ";
  }
  cout << endl << endl;
}
void dispRow(vector<char> row)
{
  cout << "row:" << endl;
  for(int i = 0; i < row.size(); i++)
  {
    cout << row[i] << " ";
  }
  cout << endl << endl;
}
void dispCol(vector<char> col)
{
  cout << "col:" << endl;
  for(int i = 0; i < col.size(); i++)
  {
    cout << col[i] << endl;
  }
  cout << endl;
}
void dispBlock(string name, Block block)
{
  cout << name << "(size: " << block.getSize() << ", length: " << block.getLength() << ", full: " << block.isFull() << "):" << endl;
  int length = 0;
  for(int y = 0; y < block.getSize(); y++)
  {
    for(int x = 0; x < block.getSize(); x++)
    {
      if(length < block.getLength())
      {
        cout << *block.getBlock()[y][x] << " ";
        length++;
      }
      else
      {
        cout << '-' << " ";
      }
    }
    cout << endl;
  }
  cout << endl;
}

int main()
{
  //// settup ////
  // var:
  int size;
  int len;
  bool full;
  vector<char> row;
  vector<char> col;
  vector<char> stars{'*', '*', '*', '*'};
  int length = 16;
  char* characters = new char[length];
  for(int i = 0; i < length; i++)
  {
    characters[i] = 'a' + i;
  }
  string pause;

  //// testing ////
  cout << "BLOCK TESTING" << endl << endl;
  dispCharacters(characters, length);
  cout << "\benter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";

  // constructors:
  cout << "Constructors:" << endl;
  Block block0; // default
  Block block1(characters, length, 0, 4); // full
  Block block2(characters, length, 2, 4); // full, not full
  Block block3(block1); // copy
  dispBlock("default", block0);
  dispBlock("full", block1);
  dispBlock("full, len-2", block2);
  dispBlock("copy", block3);
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";

  // accessors:
  cout << "Accessors:" << endl;
  size = block1.getSize(); len = block1.getLength(); full = block1.isFull();
  row = block1.getRow(0);
  col = block1.getCol(0);
  cout << "getters: " << size << ", length: " << len << ", full: " << full << endl;
  dispRow(row);
  dispCol(col);
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";

  // mutators:
  cout << "Mutators: " << endl;
  block0.load(characters, length, 0, 4);
  dispBlock("load", block0);
  block0.setRow(0, stars);
  block0.setCol(0, stars);
  dispBlock("set r[0], c[0]", block0);
  dispCharacters(characters, length);
  block0.swapRows(0, 3);
  block0.swapCols(0, 3);
  dispBlock("swap r[0] r[3], c[0] c[3]", block0);
  dispCharacters(characters, length);
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";

  //// cleanup ////
  delete[] characters;

  //// return ////
  return(0);
}
