#include <iostream>
#include "Key.h"

using namespace std;

//// declarations ////
template<typename type> void dispKey(vector<type> key);
void dispKey(string name, Key& key);

int main()
{
  //// settup ////
  // variables:
  int length = 8;
  char* characters = new char[length];
  for(int i = 0; i < length; i++) characters[i] = 'a' + i; // fill characters
  string str = "abcdefgh";
  vector<bool> lenKey;
  vector<char> valKey;
  vector<int> locKey;
  string pause;

  //// testing ////
  cout << "KEY DEBUGING" << endl << endl;
  // constructors:
  cout << "Constructors:" << endl;
  Key key0; // default
  Key key1(length); // generate
  Key key2(characters); // c-string custom
  Key key3(str); // string custom
  Key key4(key1); // copy
  dispKey("default", key0);
  dispKey("generate", key1);
  dispKey("c-string custom", key2);
  dispKey("string custom", key3);
  dispKey("copy", key4);
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";
  // save: TODO
  cout << "Save:" << endl;
  cout << "no debugging yet\n\n";
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";
  // accessors:
  cout << "Accessors:" << endl;
  lenKey = key1.lenKey();
  valKey = key1.valKey();
  locKey = key1.locKey();
  dispKey("control", key1);
  cout << "accessed values:" << endl;
  cout << "length key: ";
  dispKey(lenKey);
  cout << "value key: ";
  dispKey(valKey);
  cout << "location key: ";
  dispKey(locKey);
  cout << endl;
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";
  // mutators:
  cout << "Mutators:" << endl;
  dispKey("control", key1);
  key1.regenerate();
  dispKey("regenerated", key1);
  key1.regenerate(4);
  dispKey("regenerated, new lengths", key1);
  cout << "enter a string continue: ";
  cin >> pause;
  cout << "\n\n\n\n";
  // overloads:
  cout << "Overloads:" << endl;
  dispKey("empty control", key0);
  dispKey("control", key1);
  key0 = key1;
  cout << "empty control = control\n\n";
  dispKey("updated control", key0);
  cout << "enter a string exit: ";
  cin >> pause;
  cout << "\n\n\n\n";

  //// cleanup ////
  delete[] characters;

  //// return ////
  return(0);
}

//// definitions ////
template<typename type> void dispKey(vector<type> key)
{
  for(int i = 0; i < key.size(); i++)
  {
    cout << (int)key.at(i) << " ";
  }
  cout << endl;
}
void dispKey(string name, Key& key)
{
  cout << "Key, " << name << ":" << endl;
  cout << "  length key: ";
  dispKey<bool>(key.lenKey());
  cout << "  value key: ";
  dispKey<char>(key.valKey());
  cout << "  location key: ";
  dispKey<int>(key.locKey());
  cout << endl;
}
