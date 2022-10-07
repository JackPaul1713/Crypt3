#ifndef CYPHER_H
#define CYPHER_H

#include <vector>
#include "Key.h"
#include "SortedIndex.h"

class Cypher
{
  private:
    // attributes:
    Key key;
    // helpers:
    void encryptLen(char*& data, int& length); // encrypts length
    void decryptLen(char*& data, int& length); // decrypts length
    void encryptVal(char* data, int length); // encrypts values
    void decryptVal(char* data, int length); // decrypts values
    void encryptPos(char*& data, int length); // encrypts position
    void decryptPos(char*& data, int length); // decrypts position
    template<class numb> std::vector<numb> expandKey(std::vector<numb> key, int newLength); // lengthens key
  public:
    // constructors:
    Cypher() {} // default
    Cypher(Key key): key(key) {} // full
    Cypher(const Cypher& cypher): key(cypher.key) {} // copy
    // destructor:
    ~Cypher() {}
    // encryption:
    void encrypt(char*& bytes, int& length);
    void decrypt(char*& bytes, int& length);
    // friends:
    friend void swap(Cypher& cypher0, Cypher& cypher1) {swap(cypher0.key, cypher1.key);}
    friend void debug(); // DEBUG
    friend int compareModified(Cypher cypher, char* data, int length, char* expectedData, int expectedLength, int type); // encrypts or decrypts then compairs data, TEST
    friend int compareFinal(char* data, int length, int type); // encrypts and decrypts then compairs data, TEST
    // overloads:
    Cypher& operator=(Cypher cypher) {swap(*this, cypher); return(*this);} // assignment
};

template<class numb> std::vector<numb> Cypher::expandKey(std::vector<numb> key, int newLength) // lengthens a key
{
  // variables:
  int length = key.size();
  numb modifier = newLength; // modifier to generate new key values
  std::vector<int> expandedKey(newLength); // expanded key
  for(int i = 0; i < length && i < newLength; i++) expandedKey[i] = key[i]; // copy key to expanded key
  // expand key:
  for(int i = length; i < newLength; i++) // loop through expanded key's empty values
  {
    modifier = modifier + (expandedKey[i - length] * 2) + 1; // change modifier
    expandedKey[i] = expandedKey[i - 1] + modifier; // make new key value
  }
  // return:
  return(expandedKey);
}

#endif
