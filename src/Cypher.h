#ifndef CYPHER_H
#define CYPHER_H

#include <vector>
#include "Key.h"
// #include "Block.h"
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
    void encryptPos(char* data, int length); // encrypts position
    void decryptPos(char* data, int length); // decrypts position
    // void blockEncryptVal(Block block, int keyPos); // encrypts block values
    // void blockDecryptVal(Block block, int keyPos); // decrypts block values
    // void blockEncryptPos(Block block, int keyPos); // encrypts block position
    // void blockDecryptPos(Block block, int keyPos); // decrypts block position
    std::vector<int> expandPosKey(int newLength); // lengthens position key
  public:
    // constructors:
    Cypher() {} // default
    Cypher(Key key): key(Key(key)) {} // full
    Cypher(const Cypher& cypher): key(Key(cypher.key)) {} // copy
    // destructor:
    ~Cypher() {}
    // encryption:
    void encrypt(char* bytes, int length); // , bool block = false);
    void decrypt(char* bytes, int length); // , bool block = false);
    // friends:
    friend void swap(Cypher& cypher0, Cypher& cypher1) {swap(cypher0.key, cypher1.key);}
    friend void debug(); // DEBUG
    friend int compareEncrypted(Cypher cypher, char* data, int length, char* expectedData, int expectedLength, int type); // TEST
    friend int compareFinal(char* data, int length, int type); // TEST
    // overloads:
    Cypher& operator=(Cypher cypher) {swap(*this, cypher); return(*this);} // assignment
};

#endif
