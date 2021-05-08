#include <iostream>
#include <string>
#include "Cypher.h"

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

void test()
{
  char* key = new char[4] {'a', 'b', 'c', 'd'};
  Cypher cypher = Cypher(Key(key));
  int length = 16;
  char* data = new char(length);
  for(int i = 0; i < length; i++) data[i] = 'a' + i;
  dispCharacters(data, length);
  cypher.encryptVal(data, length);
  dispCharacters(data, length);
  cypher.decryptVal(data, length);
  dispCharacters(data, length);
}

int main()
{
  test();
  return(0);
}
