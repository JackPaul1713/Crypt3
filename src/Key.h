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
    std::vector<char> generateKey(int length); // generates key of length length(parameter)
  public:
    // constructors:
    Key() {} // default
    Key(int length): key(generateKey(length)) {} // generate
    Key(char* characters): key(std::vector<char>(characters, characters + (sizeof(characters) / sizeof(char)))) {} // custom
    Key(const Key& key): key(key.key) {} // copy
    // deconstructor:
    ~Key() {}
    // save:
    void upload(std::string filename, std::string password);
    void download(std::string filename, std::string password);
    // accessors:
    std::vector<char> getKey() {return(key);}
    char& at(int pos) {return(key.at(pos));}
    int length() {return(key.size());}
    // mutators:
    void changeLength(int newLength);
    void regenerate();
    // helpers:
    friend void swap(Key& key0, Key& key1) {key0.key.swap(key1.key);}
    // overloads:
    Key& operator=(Key key) {swap(*this, key); return(*this);}
};

#endif
