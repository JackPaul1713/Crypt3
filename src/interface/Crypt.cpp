#include <vector>
#include <string>
#include <cstrinf>
#include "Crypt.h"

using namespace std;

//// actions ////
void Crypt::reset()
{
  // reset attributes:
  data = "";
  key = "";
  full = false;
  tkey = false;
}
void Crypt::process(vector<string> values, vector<string> flags)
{
  // process flags:
  if(flags.size() > 2) // check number of flags
  {
    throw std::runtime_error("invalid arguments: flags");
  }
  for(int i = 0; i < flags.size(); i++) // loop through flags
  {
    if(flags[i] == this->flags[0].getName() || flags[i] == this->flags[0].getLetter()) // if equal to full flag
    {
      full = true;
    }
    else if(flags[i] == this->flags[1].getName() || flags[i] == this->flags[1].getLetter()) // if equal to tkey flag
    {
      tkey = true;
    }
    else // not a valid flag
    {
      throw std::runtime_error("invalid arguments: flags");
    }
  }

  // process values:
  if(values.size() != 2) // check number of values
  {
    throw std::runtime_error("invalid arguments");
  }
  try
  {
    data = file(values[0]); // set file
    if(tkey) key = values[1]; // if text key set equal to text
    else key = file(values[1]); // else set equal to file
  }
  catch(...)
  {
    throw std::runtime_error("invalid arguments");
  }
}
