#ifndef CRYPT_H
#define CRYPT_H

#include <windows.h>
#include <vector>
#include <string>
#include "Action.h"

class Crypt: public Action
{
  private:
    // helpers:
    void loadData(std::string file, char*& data, int& length); // loads file data
    void downloadData(std::string file, char* data, int length); // downloads file data
  protected:
    // attributes:
    std::string inputFile;
    std::string outputFile;
    std::string key;
    bool safe; // safe file decryption
    bool directory; // directory cryption
    bool ghost; // display only
    bool output; // output location, no overwrite
    bool tkey; // use text key
    // actions:
    void execute(std::vector<std::string> arguments); // executes action
    // helpers:
    void initiate(); // loads preset data
    void activate(); // activates input data
    void reset(); // wipes input data
    virtual void crypt(char*& data, int& dataLength, char* key, int keyLength) = 0; // instantiated for either encryption or decryption
    void buffData(char*& data, int& length); // adds two bytes to the front of data
    void debuffData(char*& data, int& length); // removes two bytes from the front of data
    void checkData(char*& data, int& length); // checks two bytes at the front of data
};

#endif
