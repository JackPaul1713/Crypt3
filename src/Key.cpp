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
Key::Key(char* rootKey, int length): // characters
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
void Key::generateRootKey(int length) // randomly generates a root key
{
  // check:
  if(length == -1) // if -1 keep current length
  {
    length = rootKey.size();
  }
  // resize:
  rootKey.resize(length);
  // generate:
  for(int i = 0; i < length; i++) // loop through key
  {
    rootKey[i] = randomChar(); // set to random character
  }
}
void Key::generateKeys() // generates keys from rootkey
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
    int piece = rootKey.size() / 8;
    int remainder = rootKey.size() % 8;
    // calculate positions:
    posKeyPosition = 0;
    valKeyPosition = piece * 3;
    lenKeyPosition = piece * 6;
    percentIncreasePosition = piece * 7;
    // calculate lenghts:
    if(rootKey.size() >= 16)
    {
      posKeyLength = piece * 3 - 3;
      valKeyLength = piece * 3;
      lenKeyLength = (piece * 2 + remainder) * 8;
    }
    else
    {
      posKeyLength = rootKey.size();
      valKeyLength = rootKey.size();
      lenKeyLength = rootKey.size();
    }
  }
  // generate position key:
  positionKey.resize(posKeyLength);
  for(int i = 0; i < posKeyLength; i++) // loop though all sets of 4 characters
  {
    positionKey[i] = rootKey[i] << 24 |
                     rootKey[i+1 % rootKey.size()] << 16 |
                     rootKey[i+2 % rootKey.size()] << 8 |
                     rootKey[i+3 % rootKey.size()]; // add integer from 4 characters
  }
  // generate value key:
  valueKey.resize(valKeyLength);
  for(int i = 0; i < valKeyLength; i++) // loop though characters
  {
    valueKey[i] = rootKey[i+valKeyPosition]; // add character
  }
  // generate length key:
  {
    unsigned int iso = 1; // bit isolater
    lengthKey.resize(lenKeyLength);
    for(int i = 0; i < lenKeyLength / 8; i++) // loop though characters
    {
      for(int j = 0; j < 8; j++) // loop through bits
      {
        lengthKey[i*8+j] = (bool)(rootKey[i+lenKeyPosition] & (iso << (7-j))); // add bool from bit
      }
    }
  }
  // generate percent increase
  percentIncrease = (float)(rootKey[percentIncreasePosition] % 13 + 12) / 100; // percent between 12 and 24
}

//// friends ////
void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.rootKey, key1.rootKey);
  swap(key0.positionKey, key1.positionKey);
  swap(key0.valueKey, key1.valueKey);
  swap(key0.lengthKey, key1.lengthKey);
  swap(key0.percentIncrease, key1.percentIncrease);
}
