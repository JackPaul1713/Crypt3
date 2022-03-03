#include <string>
#include <vector>
#include "Key.h"
#include "resources/random.h"

using namespace std;

//// constructors ////
Key::Key(int length): // generate
rootKey(), positionKey(), valueKey(), lengthKey(), percentIncrease(0)
{
  rootKey.resize(length);
  generateRootKey(length);
  generateKeys();
}
Key::Key(char* rootKey, int length): // root key
rootKey(), positionKey(), valueKey(), lengthKey(), percentIncrease(0)
{
  this->rootKey.resize(length);
  for(int i = 0; i < length; i++)
  {
    this->rootKey[i] = rootKey[i];
  }
  generateKeys();
}
Key::Key(const Key& key): // copy
rootKey(key.rootKey), positionKey(key.positionKey), valueKey(key.valueKey), lengthKey(key.lengthKey), percentIncrease(key.percentIncrease)
{}

//// mutators ////
void Key::generateRootKey(int length)
{
  if(length == -1)
  {
    length = rootKey.size();
  }
  rootKey.resize(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    rootKey[i] = randomChar(); // set to random character
  }
}
void Key::generateKeys(bool generatePosKey, bool generateValKey, bool generateLenKey, bool generatePercentIncrease)
{
  // variables:
  int posKeyPosition = 0; // start position in root key of position key
  int posKeyLength = rootKey.size();
  int valKeyPosition; // start position in root key of value key
  int valKeyLength = rootKey.size();
  int lenKeyPosition; // start position in root key of position key
  int lenKeyLength = rootKey.size();
  bool percentIncreasePosition; // position of percentIncrease seed
  // calculate lengths:
  {
    // variables:
    int piece = rootKey.size() / 4;
    int remainder = rootKey.size() % 4;
    // calculate positions:
    posKeyPosition = 0;
    valKeyPosition = piece;
    lenKeyPosition = piece * 2;
    percentIncreasePosition = piece * 3;
    // calculate lenghts:
    posKeyLength = piece * 4;
    valKeyLength = piece * 3 + remainder;
    lenKeyLength = (piece * 2 + remainder) * 8;
  }
  // generate position:
  if(generatePosKey)
  {
    positionKey.resize(posKeyLength);
    for(int i = 0; i < posKeyLength; i++) // loop though all sets of 4 characters
    {
      positionKey[i] = rootKey[i] << 24 |
                       rootKey[i+1 % rootKey.size()] << 16 |
                       rootKey[i+2 % rootKey.size()] << 8 |
                       rootKey[i+3 % rootKey.size()]; // add integer from 4 characters
    }
  }
  // generate value:
  if(generateValKey)
  {
    valueKey.resize(valKeyLength);
    for(int i = 0; i < valKeyLength; i++) // loop though characters
    {
      valueKey[i] = rootKey[i+valKeyPosition]; // add character
    }
  }
  // generate length:
  if(generateLenKey)
  {
    // var:
    unsigned int iso = 1; // bit isolater
    // generation:
    lengthKey.resize(lenKeyLength);
    for(int i = 0; i < lenKeyLength / 8; i++) // loop though characters
    {
      for(int j = 0; j < 8; j++) // loop through bits
      {
        lengthKey[i*8+j] = (bool)(rootKey[i+lenKeyPosition] & (iso << 7-j)); // add bool from bit
      }
    }
  }
  // generate percentIncrease
  if(generatePercentIncrease)
  {
    percentIncrease = (float)(rootKey[percentIncreasePosition] % 10 + 11) / 100; // percent between 11 and 20
  }
}

//// helpers ////
void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.rootKey, key1.rootKey);
  swap(key0.positionKey, key1.positionKey);
  swap(key0.valueKey, key1.valueKey);
  swap(key0.lengthKey, key1.lengthKey);
  swap(key0.percentIncrease, key1.percentIncrease);
}
