#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "Crypt.h"
#include "../resources/fileops.h"
#include "../resources/random.h"

using namespace std;

//// actions ////
void Crypt::execute(vector<string> arguments) // executes action
{
  cout << "  executing action" << endl; // DEBUG
  // variables:
  char* key;
  int keyLength;
  char* data;
  int dataLength;
  string name = this->inputFile;
  FILETIME created;
  FILETIME modified;
  FILETIME accessed;
  // settup:
  this->process(arguments);
  // load data:
  if(this->tkey)
  {
    strcpy(key, this->key.c_str()); // use text as key // FIXME
    keyLength = this->key.size();
  }
  else
  {
    if(!exists(this->key)) // if file does not exist
    {
      cout << "ERROR: " << " does not exist" << endl;
      exit(1);
    }
    key = readFile(this->key); // load key from file
    keyLength = fileLength(this->key);
  }
  loadData(this->inputFile, data, dataLength, created, modified, accessed); // load data
  // modify data:
  crypt(data, dataLength, name, created, modified, accessed, key, keyLength);
  // output data:
  if(this->ghost)
  {
    cout << data << endl; // output data to consel
    cout << "    data output" << endl; // DEBUG
  }
  else if(this->output)
  {
    downloadData(this->outputFile, data, dataLength, created, modified, accessed); // write data to file
    cout << "    data downloaded" << endl; // DEBUG
  }
  else
  {
    downloadData(this->inputFile, data, dataLength, created, modified, accessed); // overwrite data to file
    renameFile(this->inputFile, name);
    cout << "    data downloaded (overwriten)" << endl; // DEBUG
  }
  // cleanup:
  this->reset();
}

//// helpers ////
void Crypt::initiate()
{
  this->flags = {Flag("safe", 's'), Flag("directory", 'd'), Flag("ghost", 'g', {'o'}), Flag("output", 'o', {'g'}), Flag("tkey", 't')};
}
void Crypt::activate()
{
  cout << "    activating flags" << endl; // DEBUG
  // activate flags:
  for(int i = 0; i < this->selectedFlags.size(); i++)
  {
    switch(this->selectedFlags[i].getLetter())
    {
      case 's':
        this->safe = true;
        break;
      case 'd':
        this->directory = true;
        break;
      case 'g':
        this->ghost = true;
        break;
      case 'o':
        this->output = true;
        break;
      case 't':
        this->tkey = true;
        break;
    }
  }
  // activate values:
  if(this->output)
  {
    // check:
    if(this->values.size() < 3)
    {
      cout << "ERROR: "<< "too few values" << ": " << this->values.size() << endl;
      exit(1);
    }
    if(this->values.size() > 3)
    {
      cout << "ERROR: "<< "too many values" << ": " << this->values.size() << endl;
      exit(1);
    }
    // set values:
    this->inputFile = this->values[0];
    this->outputFile = this->values[1];
    this->key = this->values[2];
  }
  else
  {
    // check:
    if(this->values.size() < 2)
    {
      cout << "ERROR: "<< "too few values" << ": " << this->values.size() << endl;
      exit(1);
    }
    if(this->values.size() > 2)
    {
      cout << "ERROR: "<< "too many values" << ": " << this->values.size() << endl;
      exit(1);
    }
    // set values:
    this->inputFile = this->values[0];
    this->key = this->values[1];
  }
}
void Crypt::reset()
{
  // reset attributes:
  this->inputFile = "";
  this->outputFile = "";
  this->key = "";
  this->safe = false;
  this->directory = false;
  this->ghost = false;
  this->output = false;
  this->tkey = false;
}
void Crypt::loadData(string file, char*& data, int& length, FILETIME& created, FILETIME& modified, FILETIME& accessed)
{
  cout << "    loading data" << endl; // DEBUG
  if(!exists(file)) // if file does not exist
  {
    cout << "ERROR: " << " does not exist" << endl;
    exit(1);
  }
  data = readFile(file);
  length = fileLength(file);
  getFileTimes(file, created, modified, accessed);
}
void Crypt::downloadData(string file, char* data, int length, FILETIME created, FILETIME modified, FILETIME accessed)
{
  cout << "    downloading data" << endl; // DEBUG
  writeFile(file, data, length);
  setFileTimes(file, created, modified, accessed);
}
void Crypt::buffData(char*& data, int& length) // adds two bytes to the front of data
{
  // variables:
  int newLength = length + 2;
  char* newData = new char[newLength];
  // buffer:
  newData[0] = randomInt(0) % 4;
  newData[1] = randomInt(0) % 4;
  // fill:
  for(int i = 0; i < length; i++)
    newData[i+2] = data[i];
  // return:
  delete[] data;
  data = newData;
  length = newLength;
}
void Crypt::debuffData(char*& data, int& length) // removes two bytes from the front of data
{
  // variables:
  int newLength = length - 2;
  char* newData = new char[newLength];
  // fill:
  for(int i = 0; i < newLength; i++)
    newData[i] = data[i+2];
  // return:
  delete[] data;
  data = newData;
  length = newLength;
}
void Crypt::checkData(char*& data, int& length) // checks two bytes at the front of data
{
  // check:
  if(length < 2 || ((unsigned char)data[0] >= 4 || (unsigned char)data[1] >= 4))
  {
    cout << "ERROR: "<< "invalid decryption" << endl;
    exit(1);
  }
}
/*
void Crypt::condenceData(char*& data, int& length, string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties inside file data
{
  cout << "      condenceing data" << endl; // DEBUG
  // variables:
  int pos = 0; // position in new data
  int nameLength = name.length(); // length of name
  int newLength = nameLength + 1 + 4 * 2 * 3 + length; // new data length
  char* newData = new char[newLength]; // new data
  string newName = "";
  FILETIME blank; // empty file time
  // set :
  for(int i = 0; i < 16; i++)
  {
    newName = newName + randomFileChar(name[i]);
  }
  blank.dwLowDateTime = 0xF06C58F0;
  blank.dwHighDateTime = 0x7FFF35f4;
  // condence:
  for(int i = 0; i < nameLength; i++) // loop through characters in name
  {
    newData[pos] = name[i]; // add name to new data
    pos++;
  }
  newData[pos] = ':'; // add seperator after name
  pos++;
  for(int i = 0; i < 4; i++) // loop through characters in time integers
  {
    // created time:
    newData[pos] = created.dwLowDateTime << 4 * (3 - i); // set data position to low time integer byteshifted by i bytes (4i bits)
    newData[pos+4] = created.dwHighDateTime << 4 * (3 - i); // set data position to high time integer byteshifted by i bytes (4i bits)
    // modified time:
    newData[pos+8] = modified.dwLowDateTime << 4 * (3 - i); // set data position to low time integer byteshifted by i bytes (4i bits)
    newData[pos+12] = modified.dwHighDateTime << 4 * (3 - i); // set data position to high time integer byteshifted by i bytes (4i bits)
    // accessed time:
    newData[pos+16] = accessed.dwLowDateTime << 4 * (3 - i); // set data position to low time integer byteshifted by i bytes (4i bits)
    newData[pos+20] = accessed.dwHighDateTime << 4 * (3 - i); // set data position to high time integer byteshifted by i bytes (4i bits)
    pos++;
  }
  pos = pos + 4 * 4; // account for modified and accessed low time and high time bits
  for(int i = 0; i < length; i++) // loop through data
  {
    newData[pos] = data[i]; // add data to new data
    pos++;
  }
  // clear file data:
  name = newName;
  created = blank;
  modified = blank;
  accessed = blank;
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Crypt::expandData(char*& data, int& length, string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties back outside file data
{
  cout << "      expanding data" << endl; // DEBUG
  // variables:
  int pos = 0; // position in new data
  int newLength; // length of new data
  char* newData; // new data
  string error; // error message
  // expand:
  name = "";
  while(data[pos] != ':') // iterate through characters in name
  {
    // catch:
    if((data[pos] < 32 && data[pos] != 127) && length > pos + 24) // if invalid file character
    {
      error = "invalid contained file data";
      cout << "ERROR: "<< error << endl;
      throw std::runtime_error(error);
    }
    name = name + data[pos]; // get name from data
    pos++;
  }
  pos++; // skip seperator
  for(int i = 0; i < 4; i++) // loop through characters in time
  {
    // created time:
    created.dwLowDateTime = created.dwLowDateTime << 4 * i | data[pos]; // byteshift low time bytes over and set lowest byte to data position
    created.dwHighDateTime = created.dwHighDateTime << 4 * i | data[pos+4]; // byteshift high time bytes over and set lowest byte to data position
    // modified time:
    modified.dwLowDateTime = modified.dwLowDateTime << 4 * i | data[pos+8]; // byteshift low time bytes over and set lowest byte to data position
    modified.dwHighDateTime = modified.dwHighDateTime << 4 * i | data[pos+12]; // byteshift high time bytes over and set lowest byte to data position
    // accessed time:
    accessed.dwLowDateTime = accessed.dwLowDateTime << 4 * i | data[pos+16]; // byteshift low time bytes over and set lowest byte to data position
    accessed.dwHighDateTime = accessed.dwHighDateTime << 4 * i | data[pos+20]; // byteshift high time bytes over and set lowest byte to data position
    pos++;
  }
  pos = pos + 4 * 4; // account for modified and accessed low time and high time bits
  newLength = length - pos;
  newData = new char[newLength];
  for(int i = 0; i < newLength; i++) // loop through data
  {
    newData[i] = data[i+pos]; // add data to new data
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
*/
