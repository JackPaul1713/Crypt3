#ifndef KEY_H
#define KEY_H

#include <string>
#include <vector>
#include "Cypher.h"

class Key
{
  private:
    // attributes:
    std::vector<char> key;
    // helpers:
    char generateRandomByte(int number, int modifier);
    std::vector<char> generateKey(); // generates key of lenght length(attribute)
  public:
    // constructors:
    Key() {} // default
    Key(int length); // generate
    Key(char* characters); // custom
    Key(const Key& key); // copy
    // deconstructor:
    ~Key();
    // save:
    void upload(string filename, string password);
    void download(string filename, string password);
    // accessors:
    std::vector<char> getKey() {return(key);}
    // mutators:
    void changeLength(int newLength);
    void regenerate();
    // helpers:
    friend void swap(Key& key0, Key& key1);
    // overloads:
    Key& operator=(Key key);
};

#endif
