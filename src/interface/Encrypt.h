#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <string>
#include "Crypt.h"

class Encrypt: public Crypt
{
  protected:
    // helpers:
    void crypt(char*& data, int& dataLength, std::string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed, char* key, int keyLength);
  public:
    // constructors:
    Encrypt() {initiate();} // default
    Encrypt(const Encrypt& encrypt); // copy
    // destructor:
    ~Encrypt() {}
    // helpers:
    void initiate() {this->name="encrypt"; this->letter='e'; Crypt::initiate();}
    // friends:
    friend void swap(Encrypt e0, Encrypt e1);
    // overloads:
    Encrypt& operator=(Encrypt encrypt) {swap(*this, encrypt); return(*this);} // assignment
};

#endif
