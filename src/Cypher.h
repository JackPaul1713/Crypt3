#ifndef CYPHER_H
#define CYPHER_H

#include <vector>
#include "Block.h"
#include "Key.h"

class Key;

class Cypher
{
  private:
    // attributes:
    Key key;
    // helpers
    int find(int val, const std::vector<int> nums);
    int findNot(int val, const std::vector<int> nums);
    std::vector<int> getSortedIndex(const std::vector<char> seg, int pos); // gets the indexs of a vector sorted by the vectors values
    std::vector<int> getUnsortedIndex(const std::vector<char> seg, int pos); // gets the inverse of indexs of a vector sorted by the vectors values
    // encryption helpers:
    void encryptLen(char*& data, int& length); // encrypts length
    void decryptLen(char*& data, int& length); // decrypts length
    void encryptVal(char* data, int length); // encrypts values
    void decryptVal(char* data, int length); // decrypts values
    void encryptPos(char* data, int length); // encrypts position
    void decryptPos(char* data, int length); // decrypts position
    void blockEncryptVal(Block block, int keyPos); // encrypts block values
    void blockDecryptVal(Block block, int keyPos); // decrypts block values
    void blockEncryptPos(Block block, int keyPos); // encrypts block position
    void blockDecryptPos(Block block, int keyPos); // decrypts block position
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
    void encryptFile(std::string filename, bool block = false);
    void decryptFile(std::string filename, bool block = false);
    // friends:
    friend void swap(Cypher& cypher0, Cypher& cypher1) {swap(cypher0.key, cypher1.key);}
    friend void test();
    // overloads:
    Cypher& operator=(Cypher cypher) {swap(*this, cypher); return(*this);} // assignment
};

#endif
