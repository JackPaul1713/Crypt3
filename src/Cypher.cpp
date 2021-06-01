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
  // cout << "Cypher::encryptLen(char*& data: " << data << ", int& length: " << length << ")\n"; // DEBUG
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0;
  int dataPos = 0;
  int increase = length * key.percentIncrease();
  int newLength;
  char* newData;
  // resize:
  newLength = length + increase;
  newData = new char[newLength];
  // cout << "  new length: " << newLength << endl; // DEBUG
  // fill:
  for(int i = 0; i < newLength; i++)
  {
    if((lenKey.at(keyPos) == true && increase > 0) || dataPos >= length)
    {
      newData[i] = randomChar();
      increase--;
    }
    else
    {
      newData[i] = data[dataPos];
      dataPos++;
    }
    keyPos++;
    if(keyPos >= lenKey.size())
    {
      keyPos = 0;
    }
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Cypher::decryptLen(char*& data, int& length) // decrypts length, TODO
{
  // cout << "Cypher::encryptLen(char*& data: " << data << ", int& length: " << length << ")\n"; // DEBUG
  // variables:
  vector<bool> lenKey = key.lenKey();
  int keyPos = 0;
  int newDataPos = 0;
  int decrease = (length / (1 + key.percentIncrease())) * key.percentIncrease();
  int newLength;
  char* newData;
  // resize:
  newLength = length - decrease;
  newData = new char[newLength];
  // fill:
  for(int i = 0; i < length; i++)
  {
    if((lenKey.at(keyPos) == true && decrease > 0) || newDataPos >= length)
    {
      decrease--;
    }
    else
    {
      newData[newDataPos] = data[i];
      newDataPos++;
    }
    keyPos++;
    if(keyPos >= lenKey.size())
    {
      keyPos = 0;
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
