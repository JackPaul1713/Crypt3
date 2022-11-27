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
  // settup:
  this->process(arguments);
  // load data:
  if(this->tkey)
  {
    strcpy(key, this->key.c_str()); // use text as key
    keyLength = this->key.size();
  }
  else
  {
    loadData(this->key, key, keyLength);
  }
  loadData(this->inputFile, data, dataLength); // load data
  // modify data:
  crypt(data, dataLength, key, keyLength);
  // output data:
  if(this->ghost)
  {
    cout << data << endl; // output data to consel
    cout << "    data output" << endl; // DEBUG
  }
  else if(this->output)
  {
    downloadData(this->outputFile, data, dataLength); // write data to file
    cout << "    data downloaded" << endl; // DEBUG
  }
  else
  {
    downloadData(this->inputFile, data, dataLength); // overwrite data to file
    cout << "    data downloaded (overwriten)" << endl; // DEBUG
  }
  cout << "complete" << endl; // DEBUG
  // cleanup:
  delete[] key;
  delete[] data;
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
      cerr << "ERROR: "<< "too few values" << ": " << this->values.size() << endl;
      exit(1);
    }
    if(this->values.size() > 3)
    {
      cerr << "ERROR: "<< "too many values" << ": " << this->values.size() << endl;
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
      cerr << "ERROR: "<< "too few values" << ": " << this->values.size() << endl;
      exit(1);
    }
    if(this->values.size() > 2)
    {
      cerr << "ERROR: "<< "too many values" << ": " << this->values.size() << endl;
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
void Crypt::loadData(string file, char*& data, int& length)
{
  cout << "    loading data" << endl; // DEBUG
  if(!exists(file)) // if file does not exist
  {
    cerr << "ERROR: file " << file << " does not exist" << endl;
    exit(1);
  }
  data = readFile(file);
  length = fileLength(file);
}
void Crypt::downloadData(string file, char* data, int length)
{
  cout << "    downloading data" << endl; // DEBUG
  writeFile(file, data, length);
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
    cerr << "ERROR: "<< "invalid decryption" << endl;
    exit(1);
  }
}
