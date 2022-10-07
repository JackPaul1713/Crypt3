#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Action.h"

using namespace std;

//// helpers ////
void Action::process(std::vector<string>& arguments)
{
  // variables:
  vector<string> names; // flag names
  string error; // error message
  // find names and values:
  for(int i = 0; i < arguments.size(); i++)
  {
    if(arguments[i][0] == '-') // if argument is a flag name
    {
      cout << "flag name found: " << arguments[i] << endl; // DEBUG
      arguments[i].erase(remove(arguments[i].begin(), arguments[i].end(), '-'), arguments[i].end()); // remove dash
      names.push_back(arguments[i]); // add to flag names
      arguments.erase(arguments.begin()+i); i--; // remove used argument
    }
    else // if argument is a value
    {
      cout << "value found: " << arguments[i] << endl; // DEBUG
      this->values.push_back(arguments[i]); // add to values
      arguments.erase(arguments.begin()+i); i--; // remove used argument
    }
  }
  // find flags:
  for(int i = 0; i < names.size(); i++) // loop through flag names
  {
    for(int j = 0; j < this->flags.size(); j++) // loop through action flags
    {
      if(names[i] == this->flags[j].getName() || names[i][0] == this->flags[j].getLetter()) // if flag name matchs flag
      {
        cout << "flag found: " << this->flags[j].getName() << endl; // DEBUG
        this->selectedFlags.push_back(this->flags[j]); // select flag
        break;
      }
    }
  }
  // check flag incompatibilities:
  for(int i = 0; i < this->selectedFlags.size(); i++) // loop through selected flags
  {
    for(int j = 0; j < this->selectedFlags.size(); j++) // loop through selected flags
    {
      for(int k = 0; k < this->selectedFlags[i].getIncompatibilities().size(); k++) // loop through incompatibilities
      {
        if(this->selectedFlags[j].getLetter() == selectedFlags[i].getIncompatibilities()[k]) // if selected flag is incompatibile flag
        {
          string sflag(1, this->selectedFlags[i].getLetter()); // selected flag
          string iflag(1, this->selectedFlags[j].getLetter()); // incompatible flag
          error = "incompatibile flags: " + sflag + ", " + iflag;
          cout << "ERROR: "<< error << endl;
          throw std::runtime_error(error);
        }
      }
    }
  }
  // activate flags:
  this->activate();
}
