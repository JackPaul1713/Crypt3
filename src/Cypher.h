#ifndef CYPHER_H
#define CYPHER_H

#include <vector>
#include "Block.h"
#include "Key.h"

class Cypher
{
  private:
    // attributes:
    Key key;
    // helpers
    int find(int val, const std::vector<int> nums);
    int findNot(int val, const std::vector<int> nums);
    std::vector<int> getSortedIndex(const std::vector<char> seg, int pos);
    std::vector<int> getUnsortedIndex(const std::vector<char> seg, int pos);
    // encryption helpers:
    encryptLen(char* data, int length); // encrypts length
    decryptLen(char* data, int length); // decrypts length
    encryptVal(char* data, int length); // encrypts values
    decryptVal(char* data, int length); // decrypts values
    encryptPos(char* data, int length); // encrypts position
    decryptPos(char* data, int length); // decrypts position
    blockEncryptVal(Block block, int keyPos); // encrypts block values
    blockDecryptVal(Block block, int keyPos); // decrypts block values
    blockEncryptPos(Block block, int keyPos); // encrypts block position
    blockDecryptPos(Block block, int keyPos); // decrypts block position
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
    friend void swap(Cypher& cypher0, Cypher& cypher1) {Key::swap(cypher0.key, cypher1.key);}
    // overloads:
    Cypher& operator=(Cypher cypher) {Cypher::swap(*this, cypher); return(*this);} // assignment
}

#endif
