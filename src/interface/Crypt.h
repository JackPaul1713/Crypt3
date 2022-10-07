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
    void loadData(std::string file, char*& data, int& length, std::string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed); // loads file data
    void downloadData(std::string file, char* data, int length, std::string name, FILETIME created, FILETIME modified, FILETIME accessed); // downloads file data
  protected:
    // attributes:
    std::string inputFile;
    std::string outputFile;
    std::string key;
    bool directory; // directory encryption
    bool full; // full file cryption
    bool ghost; // display only
    bool output; // output location, no overwrite
    bool tkey; // use text key
    // actions:
    void execute(std::vector<std::string> arguments); // executes action
    // helpers:
    void initiate(); // loads preset data
    void activate(); // activates input data
    void reset(); // wipes input data
    virtual void crypt(char*& data, int& dataLength, std::string name, FILETIME created, FILETIME modified, FILETIME accessed, char* key, int keyLength) = 0; // instantiated for either encryption or decryption
    void condenceData(char*& data, int& length, std::string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed); // move file data inside file
    void expandData(char*& data, int& length, std::string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed); // move file data back outside file
};

#endif
