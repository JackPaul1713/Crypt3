#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "Crypt.h"
#include "../resources/fileops.h"

using namespace std;

//// actions ////
void Crypt::execute(vector<string> arguments) // executes action
{
  cout << "executing action" << endl; // DEBUG
  // variables:
  char* key;
  int keyLength;
  char* data;
  int dataLength;
  string name;
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
    key = readFile(this->key); // load key from file
    keyLength = fileLength(this->key);
  }
  loadData(this->inputFile, data, dataLength, name, created, modified, accessed); // load data
  cout << "data loaded" << endl; // DEBUG
  // modify data:
  crypt(data, dataLength, name, created, modified, accessed, key, keyLength);
  cout << "data modified" << endl; // DEBUG
  // output data:
  if(this->output)
  {
    downloadData(this->outputFile, data, dataLength, name, created, modified, accessed); // write data to file
    cout << "data downloaded" << endl; // DEBUG
  }
  else if(this->ghost)
  {
    cout << data << endl; // output data to consel
    cout << "data output" << endl; // DEBUG
  }
  else
  {
    downloadData(this->inputFile, data, dataLength, name, created, modified, accessed); // overwrite data to file
    cout << "data downloaded (overwriten)" << endl; // DEBUG
  }
  // cleanup:
  this->reset();
}

//// helpers ////
void Crypt::initiate()
{
  this->flags = {Flag("directory", 'd'), Flag("full", 'f', {'g'}), Flag("ghost", 'g', {'f'}), Flag("output", 'o'), Flag("tkey", 't')};
}
void Crypt::activate()
{
  cout << "activating flags" << endl; // DEBUG
  // variables:
  string error = "";
  // activate flags:
  for(int i = 0; i < this->selectedFlags.size(); i++)
  {
    switch(this->selectedFlags[i].getLetter())
    {
      case 'd':
        this->directory = true;
        break;
      case 'f':
        this->full = true;
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
    cout << "output = true" << endl; // DEBUG
    // check:
    if(this->values.size() < 3)
    {
      error = "too few values";
      cout << "ERROR: "<< error << ": " << this->values.size() << endl;
      throw std::runtime_error(error);
    }
    if(this->values.size() > 3)
    {
      error = "too many values";
      cout << "ERROR: "<< error << ": " << this->values.size() << endl;
      throw std::runtime_error(error);
    }
    // set values:
    this->inputFile = this->values[0];
    this->outputFile = this->values[1];
    this->key = this->values[2];
  }
  else
  {
    cout << "output = false" << endl; // DEBUG
    // check:
    if(this->values.size() < 2)
    {
      error = "too few values";
      cout << "ERROR: "<< error << ": " << this->values.size() << endl;
      throw std::runtime_error(error);
    }
    if(this->values.size() > 2)
    {
      error = "too many values";
      cout << "ERROR: "<< error << ": " << this->values.size() << endl;
      throw std::runtime_error(error);
    }
    // set values:
    this->inputFile = this->values[0];
    this->key = this->values[1];
  }
}
void Crypt::reset()
{
  // reset attributes:
  inputFile = "";
  outputFile = "";
  key = "";
  directory = false;
  full = false;
  ghost = false;
  output = false;
  tkey = false;
}
void Crypt::loadData(string file, char*& data, int& length, string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed) // TODO
{
  name = file; // get only end of file path // TODO
  data = readFile(file);
  length = fileLength(file);
  getFileTimes(file, created, modified, accessed);
}
void Crypt::downloadData(string file, char* data, int length, string name, FILETIME created, FILETIME modified, FILETIME accessed)
{
  writeFile(file, data, length);
  setFileTimes(file, created, modified, accessed);
  renameFile(file, name);
}
void Crypt::condenceData(char*& data, int& length, string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties inside file data // TODO
{
  // variables:
  int pos = 0; // position in new data
  int nameLength = name.length(); // length of name
  int newLength = nameLength + 1 + 4 * 2 * 3 + length; // new data length
  char* newData = new char[newLength]; // new data
  FILETIME blank; // empty file time
  blank.dwLowDateTime = 0;
  blank.dwHighDateTime = 0;
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
  name = "";
  created = blank;
  modified = blank;
  accessed = blank;
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
void Crypt::expandData(char*& data, int& length, string& name, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties back outside file data // TODO
{
  // variables:
  int pos = 0; // position in new data
  int newLength; // length of new data
  char* newData; // new data
  // expand:
  name = "";
  while(data[pos] != ':') // iterate through characters in name
  {
    name.push_back(data[pos]); // get name from data
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
