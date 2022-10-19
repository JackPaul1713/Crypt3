#ifndef DECRYPT_H
#define DECRYPT_H

#include <string>
#include "Crypt.h"

class Decrypt: public Crypt
{
  protected:
    // helpers:
    void crypt(char*& data, int& dataLength, std::string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed, char* key, int keyLength);
  public:
    // constructors:
    Decrypt() {initiate();} // default
    Decrypt(const Decrypt& decrypt); // copy
    // destructor:
    ~Decrypt() {}
    // helpers:
    void initiate() {this->name="decrypt"; this->letter='d'; Crypt::initiate();}
    // friends:
    friend void swap(Decrypt d0, Decrypt d1);
    // overloads:
    Decrypt& operator=(Decrypt decrypt) {swap(*this, decrypt); return(*this);} // assignment
};

#endif
