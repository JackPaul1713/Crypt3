#include <vector>
#include "Block.h"
#include "Key.h"
#include "Cypher.h"

//// encryption ////
void Cypher::encrypt(char* bytes, int length, bool block = false)
{

}
void Cypher::decrypt(char* bytes, int length, bool block = false)
{

}
void Cypher::encryptFile(std::string filename, bool block = false)
{

}
void Cypher::decryptFile(std::string filename, bool block = false)
{

}

//// helpers ////
int Cypher::find(int val, const std::vector<int> nums)
{

}
int Cypher::findNot(int val, const std::vector<int> nums)
{

}
std::vector<int> Cypher::getSortedIndex(const std::vector<char> seg, int pos)
{

}
std::vector<int> Cypher::getUnsortedIndex(const std::vector<char> seg, int pos)
{

}

//// encryption helpers ////
void Cypher::encryptLen(char*& data, int length) // encrypts length
{

}
void Cypher::decryptLen(char*& data, int length) // decrypts length
{

}
void Cypher::encryptVal(char* data, int length) // encrypts values
{
  // variables:
  int pos = 0; // data position
  int prevPos = 0; // previous data position
  // add key:
  if(length > key.length()) // if data is longer than the key
  {
    for(int i = 0; i < key.length(); i++) // loop through key
    {
      data[i] += key.at(i); // add key to data
    }
    pos += key.length(); // move data position up by key length
    // keep previous data position at 0
  }
  // add previous:
  while((pos + key.length()) < length) // while next data position is less than length
  {
    for(int i = 0; i < key.length(); i++) // loop through key
    {
      data[pos] += data[prevPos]; // add previous data position to data position
      pos++;
      prevPos++;
    }
  }
  for(int i = pos; i < length; i++) // loop through remaining data
  {
    data[pos] += data[prevPos]; // add previous data position to data position
    pos++;
    prevPos++;
  }
}
void Cypher::decryptVal(char* data, int length) // decrypts values
{
  // variables:
  int pos = length - 1; // data position
  int prevPos = (length - key.length()) - 1; // prevoius data position
  // subtract previous:
  if(prevPos > 0) // if previous position is greater than zero
  {
    for(int i = 0; i < (length % key.length()); i++) // loop through remaining data
    {
      data[pos] -= data[prevPos]; // subtract previous data position from data position
      pos--;
      prevPos--;
    }
  }
  while(prevPos > 0) // while previous data position is greater than zero
  {
    for(int i = 0; i < key.length(); i++) // loop through key
    {
      data[pos] -= data[prevPos]; // subtract previous data position from data position
      pos--;
      prevPos--;
    }
  }
  // subtract key:
  for(int i = 0; i < key.length(); i++) // loop through key
  {
    data[i] -= key.at(i); // subtract key from data
  }
}
void Cypher::encryptPos(char* data, int length) // encrypts position
{

}
void Cypher::decryptPos(char* data, int length) // decrypts position
{

}
void Cypher::blockEncryptVal(Block block, int keyPos) // encrypts block values
{

}
void Cypher::blockDecryptVal(Block block, int keyPos) // decrypts block values
{

}
void Cypher::blockEncryptPos(Block block, int keyPos) // encrypts block position
{

}
void Cypher::blockDecryptPos(Block block, int keyPos) // decrypts block position
{

}
