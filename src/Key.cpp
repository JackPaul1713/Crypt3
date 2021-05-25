#include <string>
#include <vector>
// #include "Cypher.h"
#include "Key.h"
#include "random.h"

using namespace std;

//// constructors ////
Key::Key(int length): // generate
lenKey_(), valKey_(), locKey_()
{
  lenKey_ = generateLenKey(length);
  valKey_ = generateValKey(length);
  locKey_ = generateLocKey(length);
}
Key::Key(char* characters, int length): // c-string custom
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
Key::Key(string str): // string custom
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
Key::Key(const Key& key): // copy
lenKey_(key.lenKey_), valKey_(key.valKey_), locKey_(key.locKey_)
{}

//// save ////
void Key::upload(string filename, string password) // TODO
{

}
void Key::download(string filename, string password) // TODO
{

}

//// mutators ////
void Key::regenerate(int length, bool len, bool val, bool loc)
{
  int lenLength = length;
  int valLength = length;
  int locLenght = length;
  if(length == -1)
  {
    lenLength = lenKey_.size();
    valLength = valKey_.size();
    locLenght = locKey_.size();
  }
  if(len) lenKey_ = generateLenKey(lenLength);
  if(val) valKey_ = generateValKey(valLength);
  if(loc) locKey_ = generateLocKey(locLenght);
}

//// helpers ////
void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.lenKey_, key1.lenKey_);
  swap(key0.valKey_, key1.valKey_);
  swap(key0.locKey_, key1.locKey_);
}
std::vector<bool> Key::generateLenKey(int length) // generates length key
{
  vector<bool> lenKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    lenKey.at(i) = generateRandomBool(); // set to random boolean
  }
  return(lenKey);
}
std::vector<char> Key::generateValKey(int length) // generates value key
{
  vector<char> valKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    valKey.at(i) = generateRandomChar(); // set to random character
  }
  return(valKey);
}
std::vector<int> Key::generateLocKey(int length) // generates location key
{
  vector<int> locKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    locKey.at(i) = generateRandomInt(); // set to random integer
  }
  return(locKey);
}
