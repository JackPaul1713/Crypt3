#include <string>
#include <vector>
// #include "Cypher.h"
#include "Key.h"
#include "random.h"

using namespace std;

//// constructors ////
Key::Key(int length): // generate
percentIncrease_(0), lenKey_(), valKey_(), locKey_()
{
  percentIncrease_ = generatePercentIncreace();
  lenKey_ = generateLenKey(length);
  valKey_ = generateValKey(length);
  locKey_ = generateLocKey(length);
}
Key::Key(char* characters, int length): // c-string custom
percentIncrease_(0), lenKey_(), valKey_(), locKey_()
{
  // make keys:
  lenKey_ = vector<bool>(length);
  valKey_ = vector<char>(length);
  locKey_ = vector<int>(length);
  // set values:
  percentIncrease_ = (float)(characters[0] % 10 + 11) / 100;
  for(int i = 0; i < length; i++) // loop through c-string
  {
    lenKey_.at(i) = (bool)(characters[i] % 2); // turn into bool
    valKey_.at(i) = characters[i];
    locKey_.at(i) = (int)characters[i]; // turn into int
  }
}
Key::Key(string str): // string custom
percentIncrease_(0), lenKey_(), valKey_(), locKey_()
{
  // make keys:
  lenKey_ = vector<bool>(str.length());
  valKey_ = vector<char>(str.length());
  locKey_ = vector<int>(str.length());
  // set values:
  percentIncrease_ = (float)(str[0] % 10 + 11) / 100;
  for(int i = 0; i < str.length(); i++) // loop through string
  {
    lenKey_.at(i) = (bool)(str[i] % 2); // turn into bool
    valKey_.at(i) = str[i]; // use characters
    locKey_.at(i) = (int)str[i]; // turn into int
  }
}
Key::Key(const Key& key): // copy
percentIncrease_(key.percentIncrease_), lenKey_(key.lenKey_), valKey_(key.valKey_), locKey_(key.locKey_)
{}

//// save ////
void Key::upload(string filename, string password) // TODO
{

}
void Key::download(string filename, string password) // TODO
{

}

//// mutators ////
void Key::regenerate(int length, bool lenP, bool len, bool val, bool loc)
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
  if(lenP) percentIncrease_ = generatePercentIncreace();
  if(len) lenKey_ = generateLenKey(lenLength);
  if(val) valKey_ = generateValKey(valLength);
  if(loc) locKey_ = generateLocKey(locLenght);
}

//// helpers ////
void swap(Key& key0, Key& key1)
{
  // swap all attributes between objects:
  swap(key0.percentIncrease_, key1.percentIncrease_);
  swap(key0.lenKey_, key1.lenKey_);
  swap(key0.valKey_, key1.valKey_);
  swap(key0.locKey_, key1.locKey_);
}
float Key::generatePercentIncreace() // generates percent increase
{
  return((float)(randomInt() % 10 + 11) / 100);
}
std::vector<bool> Key::generateLenKey(int length) // generates length key
{
  vector<bool> lenKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    lenKey.at(i) = randomBool(); // set to random boolean
  }
  return(lenKey);
}
std::vector<char> Key::generateValKey(int length) // generates value key
{
  vector<char> valKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    valKey.at(i) = randomChar(); // set to random character
  }
  return(valKey);
}
std::vector<int> Key::generateLocKey(int length) // generates location key
{
  vector<int> locKey(length);
  for(int i = 0; i < length; i++) // loop through key
  {
    locKey.at(i) = randomInt(); // set to random integer
  }
  return(locKey);
}
