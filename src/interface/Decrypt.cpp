#include <vector>
#include <string>
#include <cstrinf>
#include "Encrypt.h"
#include "../resources/file.h"

void Encrypt::execute() // TODO
{
  // variables:
  char* data;
  char* key;

  // edit file properies
  if(full)
  {

  }

  // get data:
  data = readFile(this->data); // read data from file
  if(!tkey) // if text key is false
  {
    key = readFile(this->key); // read key from file
  }
  else // if text key is true
  {
    strcpy(this-key, key); // copy characters from string to cstring
  }

  // crypt
  run(data, key); // encrypt or decrypt data
}
