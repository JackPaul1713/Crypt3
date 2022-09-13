#include <vector>
#include <algorithm>
#include "Cypher.h"
#include "Key.h"
#include "SortedIndex.h"
#include "resources/random.h"

using namespace std;

//// encryption ////
void Cypher::encrypt(char*& data, int& length)
{
  encryptLen(data, length);
  encryptVal(data, length);
  encryptPos(data, length);
}
void Cypher::decrypt(char*& data, int& length)
{
  decryptPos(data, length);
  decryptVal(data, length);
  decryptLen(data, length);
}

//// helpers ////
void Cypher::encryptLen(char*& data, int& length) // encrypts length
{
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0; // position in length key
  int dataPos = 0; // position in data
  int increase = length * key.percentInc(); // number of bytes added
  int newLength = length + increase;
  char* newData = new char[newLength];
  // resize:
  for(int i = 0; i < newLength; i++) // loop through new data
  {
    if((lenKey[keyPos] == true && increase > 0) || dataPos >= length) // if length key position is true and increase is greater than zero
    {
      newData[i] = randomChar(); // add new byte
      increase--; // decrease number of bytes to be added
    }
    else
    {
      newData[i] = data[dataPos]; // add exisiting byte
      dataPos++; // increment data position
    }
    keyPos++; // increment key position
    if(keyPos >= lenKey.size()) keyPos = 0; // wrap arround length key
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::decryptLen(char*& data, int& length) // decrypts length
{
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0; // position in length key
  int newDataPos = 0; // position in new data
  int decrease = (length / (1 + key.percentInc())) * key.percentInc(); // number of bytes removed
  int newLength = length - decrease;
  char* newData = new char[newLength];
  // resize:
  for(int i = 0; i < length; i++) // loop through data
  {
    if((lenKey.at(keyPos) == true && decrease > 0) || newDataPos >= length) // if length key position is true and decrease is greater than zero
    {
      decrease--; // decrease the number of bytes to be removed
    }
    else
    {
      newData[newDataPos] = data[i]; // add byte to new data
      newDataPos++; // increment new data position
    }
    keyPos++; // increment key position
    if(keyPos >= lenKey.size()) keyPos = 0; // wrap arround length key
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::encryptVal(char* data, int length) // encrypts values
{
  // variables:
  vector<char> valKey = key.valKey();
  int pos = 0; // data position
  int prevPos = 0; // previous data position
  // add key:
  while(pos < length && pos < valKey.size()) // while within key length
  {
    data[pos] += valKey.at(pos); // add key to data position
    pos++;
  }
  // add previous:
  while(pos < length) // while remaining data exists
  {
    data[pos] += data[prevPos]; // add previous data position to data position
    pos++;
    prevPos++;
  }
}
void Cypher::decryptVal(char* data, int length) // decrypts values
{
  // variables:
  vector<char> valKey = key.valKey();
  int pos = length - 1; // data position
  int prevPos = (length - valKey.size()) - 1; // prevoius data position
  // subtract previous:
  while(pos >= valKey.size()) // while beyond length of value key
  {
    data[pos] -= data[prevPos];
    pos--;
    prevPos--;
  }
  // subtract key:
  while(pos >= 0) // while within key length
  {
    data[pos] -= valKey.at(pos);
    pos--;
  }
}
void Cypher::encryptPos(char*& data, int length) // encrypts position
{
  // variables:
  vector<int> posKey = this->expandKey(this->key.posKey(), length); // expand position key to fit data
  SortedIndex sortedIndex;
  // sort:
  sortedIndex.sort(posKey); // sort indexes by position key
  // encrypt:
  sortedIndex.sortData(data, length); // sort data by indexes
}
void Cypher::decryptPos(char*& data, int length) // decrypts position
{
  // variables:
  vector<int> posKey = this->expandKey<int>(this->key.posKey(), length); // expand position key to fit data
  SortedIndex sortedIndex;
  // sort:
  sortedIndex.invertedSort(posKey); // sort indexes by position key
  // decrypt:
  sortedIndex.sortData(data, length); // sort data by indexes
}
