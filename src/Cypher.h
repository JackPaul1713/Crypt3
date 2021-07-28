#ifndef CYPHER_H
#define CYPHER_H

#include <vector>
#include "Block.h"
#include "Key.h"

class Key;

struct SortedIndex // indexs of a vector sorted by the vectors values
{
  public:
    // attributes:
      vector<int> indexs;
    // mutators:
      void burn(int i) {indexs[i] = -1;}
      int findNext();
};

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
    void encryptPos(char* data, int length); // encrypts position
    void decryptPos(char* data, int length); // decrypts position
    // void blockEncryptVal(Block block, int keyPos); // encrypts block values
    // void blockDecryptVal(Block block, int keyPos); // decrypts block values
    // void blockEncryptPos(Block block, int keyPos); // encrypts block position
    // void blockDecryptPos(Block block, int keyPos); // decrypts block position

    std::vector<int> expandPosKey(int newLength);
    SortedIndex getSortedIndex(const std::vector<int> segment);
    SortedIndex getInvertedSortedIndex(const std::vector<int> segment); // switches sorted indexs with their indexs
  public:
    // constructors:
    Cypher() {} // default
    Cypher(Key key): key(Key(key)) {} // full
    Cypher(const Cypher& cypher): key(Key(cypher.key)) {} // copy
    // destructor:
    ~Cypher() {}
    // encryption:
    void encrypt(char* bytes, int length, bool block = false);
    void decrypt(char* bytes, int length, bool block = false);
    // friends:
    friend void swap(Cypher& cypher0, Cypher& cypher1) {swap(cypher0.key, cypher1.key);}
    friend void test();
    // overloads:
    Cypher& operator=(Cypher cypher) {swap(*this, cypher); return(*this);} // assignment
};

#endif
