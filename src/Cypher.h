#ifndef CYPHER_H
#define CYPHER_H

#include <functional>
#include <vector>
#include <string>
#include "Key.h"
#include "SortedIndex.h"

class Cypher
{
  private:
    // attributes:
    Key key; // encryption key
    std::string order; // encryption order
    // helpers:
    void encryptLen(char*& data, int& length); // encrypts length
    void decryptLen(char*& data, int& length); // decrypts length
    void encryptVal(char* data, int length); // encrypts values
    void decryptVal(char* data, int length); // decrypts values
    void encryptPos(char*& data, int length); // encrypts position
    void decryptPos(char*& data, int length); // decrypts position
    template<class numb> std::vector<numb> resizeKey(std::vector<numb> key, int newLength); // lengthens key
  public:
    // constructors:
    Cypher(): key(), order("lvp") {} // default
    Cypher(Key key, std::string order="lvp"): key(key), order(order) {} // full
    Cypher(const Cypher& cypher): key(cypher.key), order(cypher.order) {} // copy
    // destructor:
    ~Cypher() {}
    // encryption:
    void encrypt(char*& bytes, int& length);
    void decrypt(char*& bytes, int& length);
    // friends:
    friend void swap(Cypher& cypher0, Cypher& cypher1) {swap(cypher0.key, cypher1.key);}
    friend int compareModified(Cypher cypher, char* data, int length, char* expectedData, int expectedLength, int type); // encrypts or decrypts then compairs data, TESTING
    friend int compareFinal(char* data, int length, int type); // encrypts and decrypts then compairs data, TESTING
    // overloads:
    Cypher& operator=(Cypher cypher) {swap(*this, cypher); return(*this);} // assignment
};

template<class numb> std::vector<numb> Cypher::resizeKey(std::vector<numb> key, int newLength) // lengthens a key
{
  // variables:
  int length = key.size();
  numb modifier = newLength; // modifier to generate new key values
  std::vector<int> resizedKey(newLength); // resized key
  std::hash<numb> newHashVal; // generates new values
  // shrink key:
  if(newLength < length) length = newLength; // if new length is less than length
  // copy key:
  for(int i = 0; i < length; i++) resizedKey[i] = key[i]; // copy key to resized key
  // expand key:
  for(int i = length; i < newLength; i++) // loop through resized key's empty values
  {
    modifier = modifier + (resizedKey[i - length] * 2) + 1; // change modifier
    resizedKey[i] = newHashVal(resizedKey[i - 1] + modifier); // make new key value
  }
  // return:
  return(resizedKey);
}

#endif
