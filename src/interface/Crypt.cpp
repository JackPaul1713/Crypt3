#include <iostream>
#include <vector>
#include <string>
#include <cstrinf>
#include "Crypt.h"
#include "../resources/fileops.h"

using namespace std;

//// actions ////
void Crypt::execute(std::vector<std::string> arguments); // runs command
{
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
  this->activate();
  // load data:
  if(this->tkey)
  {
    strcpy(key, this->key); // use text as key
  }
  else
  {
    key = readFile(this->key);  // load key from file
  }
  loadData(this->inputFile, data, dataLength, name, created, modified, accessed); // load data
  // modify data:
  crypt(data, dataLength, name, created, modified, accessed, key, keyLength);
  // output data:
  if(this->output)
  {
    downloadData(this->outputFile, data, dataLength, name, created, modified, accessed); // write data to file
  }
  else if(this->ghost)
  {
    cout << data << endl; // output data to consel
  }
  else
  {
    downloadData(this->inputFile, data, dataLength, name, created, modified, accessed); // overwrite data to file
  }
  // cleanup:
  this->reset();
}

//// helpers ////
void Crypt::initiate()
{
  flags = {Flag("directory", 'd'), Flag("full", 'f', incompatibilities = {'g'}), Flag("ghost", 'g', incompatibilities = {'f'}), Flag("output", 'o'), Flag("tkey", 't')};
}
void Crypt::activate()
{
  // activate flags:
  for(int i = 0; i < this->selectedFlags.size(); i++)
  {
    switch(this->selectedFlags.letter)
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
    // activate values:
    if(output)
    {
      // check:
      if(this->values.size() < 3) throw std::runtime_error("too few values");
      if(this->values.size() > 3) throw std::runtime_error("too many values");
      // set values:
      this->inputFile = this->values[0];
      this->outputFile = this->values[1];
      this->key = this->values[2];
    }
    else
    {
      // check:
      if(this->values.size() < 2) throw std::runtime_error("too few values");
      if(this->values.size() > 2) throw std::runtime_error("too many values");
      // set values:
      this->inputFile = this->values[0];
      this->key = this->values[1];
    }
  }
}
void Crypt::reset()
{
  // reset attributes:
  input = "";
  output = "";
  key = "";
  directory = false;
  full = false;
  ghost = false;
  output = false;
  tkey = false;
}
void Cyrpt::loadData(string file, char*& data, int& length, FILETIME& created, FILETIME& modified, FILETIME& accessed)
{
  data = readfile(file);
  length = fileLength(file);
  getFileTimes(file, created, modified, accessed);
}
void Cyrpt::downloadData(string file, char* data, int length, FILETIME created, FILETIME modified, FILETIME accessed)
{
  writefile(file, data, length);
  setFileTimes(file, created, modified, accessed);
}
void Cyrpt::condenceData(string& name, char*& data, int& length, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties inside file data // TODO
{
  // variables:
  int pos = 0; // position in new data
  int timeLength = 8; // byte length of time
  int nameLength = name.length(); // length of name
  int newLength = nameLength + 1 + timeLength * 3 + length; // new data length
  char* newData = new char[newLength]; // new data
  FILETIME blank; // empty file time
  blank.dwLowDateTime = 0;
  blank.dwLowDateTime = 0;
  // condence:
  for(int i = 0; i < nameLength; i++) // loop through characters in name
  {
    newData[pos] = name[i]; // add name to new data
    pos++;
  }
  newData[pos] = ':'; // add seperator after name
  pos++;
  for(int i = 0; i < timeLength; i++) // loop through characters in time
  {
    newData[pos] = created << 8 * (timeLength - 1 - i); // add created time to new data
    newData[pos+timeLength] = modified << 8 * (timeLength - 1 - i); // add modified time to new data
    newData[pos+timelength*2] = accessed << 8 * (timeLength - 1 - i); // add accessed time to new data
    pos++;
  }
  pos = pos + timeLength * 2; // account for characters from accessed and modified time
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
void Cyrpt::expandData(string& name, char*& data, int& length, FILETIME& created, FILETIME& modified, FILETIME& accessed) // move file properties back outside file data // TODO
{
  // variables:
  int pos = 0; // position in new data
  int timeLength = 8; // byte length of time
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
  for(int i = 0; i < timelength; i++) // loop through characters in time
  {
    created = created << 8 * i | data[pos]; // get created from data
    modified = modified << 8 * i | data[pos+timeLength]; // get modified from data
    accessed = accessed << 8 * i | data[pos+timeLength*2]; // get accessed from data
    pos++;
  }
  pos = pos + timeLength * 2; // account for characters from accessed and modified time
  newLength = length - pos;
  newData = new char[newLength];
  for(int i = 0; i < newLength; i++) // loop through data
  {
    newData[i] = data[i+pos]; // get new data from data
  }
  // return:
  delete[] data;
  length = newLength;
  data = newData;
}
