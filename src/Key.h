#ifndef KEY_H
#define KEY_H

#include <string>
#include <vector>
#include "Cypher.h"

class Key
{
  private:
    // attributes:
    std::vector<bool> lenKey_;
    std::vector<char> valKey_;
    std::vector<int> locKey_;
    // helpers:
    char generateRandomBool() {return(rand() % 2);}
    char generateRandomByte() {return((rand() % 128) - 128);}
    char generateRandomInt() {return(rand());}
    std::vector<bool> generateLenKey(int length); // generates length key
    std::vector<char> generateValKey(int length); // generates value key
    std::vector<int> generateLocKey(int length); // generates location key
  public:
    // constructors:
    Key() {} // default
    Key(int length); // generate
    Key(char* characters, int length); // c-string custom
    Key(string str); // string custom
    Key(const Key& key); // copy
    // deconstructor:
    ~Key();
    // save:
    void upload(string filename, string password);
    void download(string filename, string password);
    // accessors:
    std::vector<bool> lenKey() {return(lenKey_);}
    std::vector<char> valKey() {return(valKey_);}
    std::vector<int> locKey() {return(locKey_);}
    // mutators:
    void changeLength(int newLength, bool len = true, bool val = true, bool loc = true);
    void regenerate(bool len = true, bool val = true, bool loc = true);
    // helpers:
    friend void swap(Key& key0, Key& key1);
    // overloads:
    Key& operator=(Key key);
};

#endif
