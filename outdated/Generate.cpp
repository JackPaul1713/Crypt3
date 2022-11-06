#include <vector>
#include <string>
#include "Generate.h"

//// actions ////
void Generate::reset()
{
  file = "";
  length = 0;
}
void Generate::process(vector<string> values, vector<string> flags)
{
  // process flags:
  if(flags.size() > 0) // check number of flags
  {
    throw std::runtime_error("invalid arguments: flags");
  }

  // process values:
  if(values.size() != 2) // check number of values
  {
    throw std::runtime_error("invalid arguments");
  }
  try
  {
    file = file(values[0]); // set file
    length = stoi(values[1]); // set length
  }
  catch(...)
  {
    throw std::runtime_error("invalid arguments");
  }
}
void Generate::execute()
{

}
