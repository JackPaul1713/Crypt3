#include <string>
#include "Encrypt.h"
#include "Cypher.h"
#include "Key.h"

void Encrypt::crypt(char*& data, int& dataLength, string name, FILETIME created, FILETIME modified, FILETIME accessed, char* key, int keyLength)
{
  // variables:
  Key enkey(key, keyLength); // encryption key
  Cypher cypher(enkey);
  // process:
  if(full)
  {
    condenceData(data, dataLength, name, created, modified, accessed);
  }
  // encrypt:
  cypher.encrypt(data, dataLength);
}
