#include <string>
#include "Encrypt.h"
#include "Cypher.h"
#include "Key.h"

void Encrypt::crypt(char*& data, int& dataLength, string name, FILETIME created, FILETIME modified, FILETIME accessed, char* key, int keyLength)
{
  // variables:
  Key dekey(key, keyLength); // decryption key
  Cypher cypher(dekey);
  // encrypt:
  cypher.decrypt(data, dataLength);
  // process:
  if(full)
  {
    expandData(data, dataLength, name, created, modified, accessed);
  }
}
