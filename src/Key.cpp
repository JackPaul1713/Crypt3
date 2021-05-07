#include <string>
#include <vector>
#include "Cypher.h"

//// constructors ////
Key(int length): // generate
lenKey_(), valKey_(), locKey_()
{
  lenKey_ = generateLenKey(length);
  valKey_ = generateValKey(length);
  locKey_ = generateLocKey(length);
}
Key(char* characters, int length): // c-string custom
lenKey_(), valKey_(), locKey_()
{
  // make keys:
  lenKey_ = vector<bool>(length);
  valKey_ = vector<char>(length);
  locKey_ = vector<int>(length);
  // set values:
  for(int i = 0; i < length; i++) // loop through c-string
  {
    lenKey_.at(i) = (bool)(characters[i] % 2); // turn into bool
    valKey_.at(i) = characters[i];
    locKey_.at(i) = (int)characters[i]; // turn into int
  }
}
Key(string str): // string custom
lenKey_(), valKey_(), locKey_()
{
  // make keys:
  lenKey_ = vector<bool>(str.length());
  valKey_ = vector<char>(str.length());
  locKey_ = vector<int>(str.length());
  // set values:
  for(int i = 0; i < str.length(); i++) // loop through string
  {
    lenKey_.at(i) = (bool)(str[i] % 2); // turn into bool
    valKey_.at(i) = str[i];
    locKey_.at(i) = (int)str[i]; // turn int int
  }
}
Key(const Key& key): // copy
lenKey_(key.lenKey_), valKey_(key.valKey_), locKey_(key.locKey_)
{}

//// save ////
void upload(string filename, string password) // TODO
{

}
void download(string filename, string password) // TODO
{

}

//// mutators ////
void changeLength(int newLength, bool len, bool val, bool loc)
{
  if(len) lenKey_ = generateLenKey(newLength);
  if(val) valKey_ = generateLenKey(newLength);
  if(loc) locKey_ = generateLenKey(newLength);
}
void regenerate(bool len, bool val, bool loc)
{
  if(len) lenKey_ = generateLenKey(lenKey_.size());
  if(val) valKey_ = generateLenKey(valKey_.size());
  if(loc) locKey_ = generateLenKey(locKey_.size());
}

//// helpers ////
friend void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.lenKey_, key1.lenKey_);
  swap(key0.valKey_, key1.valKey_);
  swap(key0.locKey_, key1.locKey_);
}
std::vector<bool> generateLenKey(int length) // generates length key
{
  vector<bool> lenKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    lenKey.at(i) = generateRandomBool(); // set to random boolean
  }
  return(lenKey);
}
std::vector<char> generateValKey(int length) // generates value key
{
  vector<bool> valKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    valKey.at(i) = generateRandomChar(); // set to random character
  }
  return(valKey);
}
std::vector<int> generateLocKey(int length) // generates location key
{
  vector<bool> locKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    locKey.at(i) = generateRandomInt(); // set to random integer
  }
  return(locKey);
}
