#include <vector>
#include <iostream> // DEBUG
#include "Cypher.h"
#include "Key.h"
// #include "Block.h"
#include "random.h"
#include "SortedIndex.h"

using namespace std;

//// encryption ////
void Cypher::encrypt(char* data, int length) // , bool block)
{
  encryptVal(data, length);
  encryptPos(data, length);
  encryptLen(data, length);
}
void Cypher::decrypt(char* data, int length) // , bool block)
{
  decryptLen(data, length);
  decryptPos(data, length);
  decryptVal(data, length);
}

//// helpers ////
void Cypher::encryptLen(char*& data, int& length) // encrypts length
{
  // cout << "Cypher::encryptLen(char*& data: " << data << ", int& length: " << length << ")\n"; // DEBUG
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0; // position in length key
  int dataPos = 0; // position in data
  int increase = length * key.percentInc(); // number of bytes added
  char* newData;
  int newLength;
  // resize:
  newLength = length + increase;
  newData = new char[newLength];
  // cout << "  new length: " << newLength << endl; // DEBUG
  // fill:
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
    if(keyPos >= lenKey.size())
    {
      keyPos = 0; // wrap arround length key
    }
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::decryptLen(char*& data, int& length) // decrypts length
{
  // cout << "Cypher::encryptLen(char*& data: " << data << ", int& length: " << length << ")\n"; // DEBUG
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0; // position in length key
  int newDataPos = 0; // position in new data
  int decrease = (length / (1 + key.percentInc())) * key.percentInc(); // number of bytes removed
  int newLength;
  char* newData;
  // resize:
  newLength = length - decrease;
  newData = new char[newLength];
  // fill:
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
    if(keyPos >= lenKey.size())
    {
      keyPos = 0; // wrap arround length key
    }
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::encryptVal(char* data, int length) // encrypts values
{
  // cout << "Cypher::encryptVal(char* data: " << data << ", int length: " << length << ")\n"; // DEBUG
  // variables:
  vector<char> valKey = key.valKey();
  int pos = 0; // data position
  int prevPos = 0; // previous data position
  if(length > valKey.size()) // if data is longer than the key
  {
    // cout << "  longer" << endl; // DEBUG
    // add key:
    // cout << "  begining: " << endl; // DEBUG
    // cout << "  "; // DEBUG
    for(int i = 0; i < valKey.size(); i++) // loop through key
    {
      // cout << (int)data[i] << "+" << (int)key.valAt(i) << " "; // DEBUG
      data[i] += valKey.at(i); // add key to data
    }
    // cout << endl; // DEBUG
    pos += valKey.size(); // move data position up by key length
                            // keep previous data position at 0
    // add previous:
    // cout << "  core: " << endl;
    while((pos + valKey.size()) <= length) // while segment exisits
    {
      // cout << "  "; // DEBUG
      for(int i = 0; i < valKey.size(); i++) // loop through key
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
      data[i] += valKey.at(i); // add key to data
    }
    // cout << endl; // DEBUG
  }
}
void Cypher::decryptVal(char* data, int length) // decrypts values
{
  // cout << "Cypher::decryptVal(char* data: " << data << ", int length: " << length << ")\n"; // DEBUG
  // variables:
  vector<char> valKey = key.valKey();
  int pos = length - 1; // data position
  int prevPos = (length - valKey.size()) - 1; // prevoius data position
  if(prevPos > 0) // if data is longer than key
  {
    // cout << "  longer" << endl; // DEBUG
    // subtract previous:
    // cout << "  end: " << endl; // DEBUG
    // cout << "  "; // DEBUG
    for(int i = 0; i < (length % valKey.size()); i++) // loop through remaining data (remaining in encryption)
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
      for(int i = 0; i < valKey.size(); i++) // loop through key
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
    for(int i = 0; i < valKey.size(); i++) // loop through key
    {
      // cout << (int)data[i] << "-" << (int)key.valAt(i) << " "; // DEBUG
      data[i] -= valKey.at(i); // subtract key from data
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
      data[i] -= valKey.at(i); // subtract key from data
    }
    // cout << endl; // DEBUG
  }
}
void Cypher::encryptPos(char* data, int length) // encrypts position, TODO
{
  // variables:
  vector<int> posKey = expandPosKey(length);
  cout << "length: " << length << ", position key length: " << posKey.size() << endl; // TEMP DEBUG
  {string trash; cout << "c to continue: "; cin >> trash;} // TEMP DEBUG
  SortedIndex sortedIndex;
  sortedIndex.sort(posKey);
  {string trash; cout << "c to continue: "; cin >> trash;} // TEMP DEBUG
  // encrypt:
  sortData(data, sortedIndex);
}
void Cypher::decryptPos(char* data, int length) // decrypts position, TODO
{
  // variables:
  vector<int> posKey = expandPosKey(length);
  SortedIndex sortedIndex;
  sortedIndex.invertedSort(posKey);
  // decrypt:
  sortData(data, sortedIndex);
}
/*
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
*/
vector<int> Cypher::expandPosKey(int length)
{
  // variables:
  int seed = fixedRandom(length);
  int modIndex = 0; // modify index (index seed is modified by)
  int begIndex = 1; // begining index
  vector<int> expantionMods = key.posKey(); // expantion modifiers
  vector<int> expandedPosKey(length); // expanded positon key
  // expand position key:
  for(int i = begIndex; i < length; i++) // loop through expanded position key
  {
    // modify:
    seed += expantionMods[modIndex]; // modify seed
    expantionMods[modIndex] = fixedRandom(seed); // overwrite used modifier
    modIndex++; // increment modify index
    if (modIndex > expantionMods.size()) modIndex = 0; // wrap modify index arround
    // expand:
    expandedPosKey[i] = fixedRandom(seed); // expand position key
  }
  // return:
  return(expandedPosKey);
}
void Cypher::sortData(char* data, SortedIndex sortedIndex)
{
  // variables:
  char value;
  int index;
  int burnIndex;
  // sort data:
  index = 0;
  value = data[0];
  while(sortedIndex.findNext() != -1)
  {
    // check index:
    if(sortedIndex.at(index) == -1) // if index has been burned (already used)
    {
      index = sortedIndex.findNext(); // get unused index
      value = data[index];
    }
    // shift index:
    burnIndex = index; // mark index for burning
    index = sortedIndex.at(index); // get next index
    sortedIndex.burn(burnIndex); // burn previous index
    // sort value:
    swap(value, data[index]); // swap current value with next value
  }
}
