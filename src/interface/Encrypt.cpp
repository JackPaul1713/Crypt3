#include <fileapi.h>
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
  FILETIME created;
  FILETIME modified;
  FILETIME accessed;
  FILETIME zero; zero.dwHighDateTime = 1; zero.dwLowDateTime = 1;

  // get properties
  if(full)
  {
    getFileTimes(this->data, created, modified, accessed); // get file times
    setFileTimes(this->data, zero, zero, zero); // set file times to min values
  }

  // get data:
  data = readFile(this->data); // read data from file
  if(!tkey) // if text key is false
  {
    key = readFile(this->key); // read key from file
  }
  else // if text key is true
  {
    strcpy(key, this->key.c_str); // copy characters from string to cstring
  }

  // crypt
  run(data, key); // encrypt or decrypt data
}
