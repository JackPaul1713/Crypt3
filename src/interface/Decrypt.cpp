#include <iostream> // DEBUG
#include <string>
#include "Decrypt.h"
#include "../Cypher.h"
#include "../Key.h"

using namespace std;

void Decrypt::crypt(char*& data, int& dataLength, char* key, int keyLength)
{
  cout << "    modifying data" << endl; //DEBUG
  // variables:
  Key dekey(key, keyLength); // decryption key
  Cypher cypher(dekey);
  // encrypt:
  cypher.decrypt(data, dataLength);
  // process:
  if(safe)
  {
    checkData(data, dataLength);
    debuffData(data, dataLength);
  }
}
