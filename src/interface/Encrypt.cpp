#include <iostream> // DEBUG
#include <string>
#include "Encrypt.h"
#include "../Cypher.h"
#include "../Key.h"

using namespace std;

void Encrypt::crypt(char*& data, int& dataLength, char* key, int keyLength)
{
  cout << "    modifying data" << endl; //DEBUG
  // variables:
  Key enkey(key, keyLength); // encryption key
  Cypher cypher(enkey);
  // process:
  if(safe)
  {
    buffData(data, dataLength);
  }
  // encrypt:
  cypher.encrypt(data, dataLength);
}
