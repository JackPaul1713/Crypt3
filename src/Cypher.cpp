#include <vector>
#include <iostream> // DEBUG
#include "Block.h"
#include "Key.h"
#include "Cypher.h"
#include "random.h"

using namespace std;

//// encryption ////
void Cypher::encrypt(char* bytes, int length, bool block) // TODO
{

}
void Cypher::decrypt(char* bytes, int length, bool block) // TODO
{

}
void Cypher::encryptFile(std::string filename, bool block) // TODO
{

}
void Cypher::decryptFile(std::string filename, bool block) // TODO
{

}

//// helpers ////
int Cypher::find(int val, const std::vector<int> nums) // TODO
{

}
int Cypher::findNot(int val, const std::vector<int> nums) // TODO
{

}
std::vector<int> Cypher::getSortedIndex(const std::vector<char> seg, int pos) // TODO
{

}
std::vector<int> Cypher::getUnsortedIndex(const std::vector<char> seg, int pos) // TODO
{

}

//// encryption helpers ////
void Cypher::encryptLen(char*& data, int& length) // encrypts length, TODO
{
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0;
  int dataPos = 0;
  int newDataPos = 0;
  int begBuff = data * 0.1;
  int endBuff = beg;
  int newLength;
  char* newData;
  // resize:
  newLength = length + begBuff + endBuff;
  newData = new char[newLength];
  // add begining:
  while(begBuff > 0)
  {
    if(begBuff > (newLength / 2 - newDataPos)) // begining buffer has extra space in the remaining first half of new data
    {
      if(lenKey.at(keyPos) == true) // if key is true
      {
        newData[i] = generateRandomChar(); // add buffer at index
        begBuff--;
        keyPos++;
      }
      else
      {
        newData[i] = data[dataPos];
        dataPos++;
      }
      newDataPos++;
    }
    else // begining buffer will completely fill the remaining first half of new data
    {

    }
  }
  // add end:
  // add data:
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::decryptLen(char*& data, int& length) // decrypts length, TODO
{

}
void Cypher::encryptVal(char* data, int length) // encrypts values
{
  // cout << "Cypher::encryptVal(char* data: " << data << ", int length" << length << ")\n"; // DEBUG
  // variables:
  int pos = 0; // data position
  int prevPos = 0; // previous data position
  if(length > key.valLength()) // if data is longer than the key
  {
    // cout << "  longer" << endl; // DEBUG
    // add key:
    // cout << "  begining: " << endl; // DEBUG
    // cout << "  "; // DEBUG
    for(int i = 0; i < key.valLength(); i++) // loop through key
    {
      // cout << (int)data[i] << "+" << (int)key.valAt(i) << " "; // DEBUG
      data[i] += key.valAt(i); // add key to data
    }
    // cout << endl; // DEBUG
    pos += key.valLength(); // move data position up by key length
                            // keep previous data position at 0
    // add previous:
    // cout << "  core: " << endl;
    while((pos + key.valLength()) <= length) // while segment exisits
    {
      // cout << "  "; // DEBUG
      for(int i = 0; i < key.valLength(); i++) // loop through key
      {
        // cout << (int)data[pos] << "+" << (int)data[prevPos] << " "; // DEBUG
        data[pos] += data[prevPos]; // add previous data position to data position
        pos++;
        prevPos++;
      }
      // cout << endl; // DEBUG
    }
    // cout << "  end: " << endl; // DEBUG
    // cout << "  "; // DEBUG
    for(int i = pos; i < length; i++) // loop through remaining data
    {
      // cout << (int)data[pos] << "+" << (int)data[prevPos] << " "; // DEBUG
      data[pos] += data[prevPos]; // add previous data position to data position
      pos++;
      prevPos++;
    }
    // cout << endl; // DEBUG
  }
  else // if data is shorter than key
  {
    // cout << "  shorter" << endl; // DEBUG
    // add key:
    // cout << "  "; // DEGUB
    for(int i = 0; i < length; i++) // loop through remaining data
    {
      // cout << (int)data[i] << "+" << (int)key.valAt(i) << " "; // DEBUG
      data[i] += key.valAt(i); // add key to data
    }
    // cout << endl; // DEBUG
  }
}
void Cypher::decryptVal(char* data, int length) // decrypts values
{
  // cout << "Cypher::decryptVal(char* data: " << data << ", int length" << length << ")\n"; // DEBUG
  // variables:
  int pos = length - 1; // data position
  int prevPos = (length - key.valLength()) - 1; // prevoius data position
  if(prevPos > 0) // if data is longer than key
  {
    // cout << "  longer" << endl; // DEBUG
    // subtract previous:
    // cout << "  end: " << endl; // DEBUG
    // cout << "  "; // DEBUG
    for(int i = 0; i < (length % key.valLength()); i++) // loop through remaining data (remaining in encryption)
    {
      // cout << (int)data[pos] << "-" << (int)data[prevPos] << " "; // DEBUG
      data[pos] -= data[prevPos]; // subtract previous data position from data position
      pos--;
      prevPos--;
    }
    // cout << endl; // DEBUG
    // cout << "  core: " << endl; // DEBUG
    while(prevPos > 0) // while previous segment exisits
    {
      // cout << "  "; // DEBUG
      for(int i = 0; i < key.valLength(); i++) // loop through key
      {
        // cout << (int)data[pos] << "-" << (int)data[prevPos] << " "; // DEBUG
        data[pos] -= data[prevPos]; // subtract previous data position from data position
        pos--;
        prevPos--;
      }
      // cout << endl; // DEBUG
    }
    // subtract key:
    // cout << "  begining: " << endl;
    // cout << "  "; // DEBUG
    for(int i = 0; i < key.valLength(); i++) // loop through key
    {
      // cout << (int)data[i] << "-" << (int)key.valAt(i) << " "; // DEBUG
      data[i] -= key.valAt(i); // subtract key from data
    }
    // cout << endl; // DEBUG
  }
  else // if data is shorter than key
  {
    // cout << "  shorter" << endl; // DEBUG
    // subtract key:
    // cout << "  "; // DEBUG
    for(int i = 0; i < length; i++) // loop through remaining data
    {
      // cout << (int)data[i] << "-" << (int)key.valAt(i) << " "; // DEBUG
      data[i] -= key.valAt(i); // subtract key from data
    }
    // cout << endl; // DEBUG
  }
}
void Cypher::encryptPos(char* data, int length) // encrypts position, TODO
{

}
void Cypher::decryptPos(char* data, int length) // decrypts position, TODO
{

}
void Cypher::blockEncryptVal(Block block, int keyPos) // encrypts block values, TODO
{

}
void Cypher::blockDecryptVal(Block block, int keyPos) // decrypts block values, TODO
{

}
void Cypher::blockEncryptPos(Block block, int keyPos) // encrypts block position, TODO
{

}
void Cypher::blockDecryptPos(Block block, int keyPos) // decrypts block position, TODO
{

}
