#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Action.h"

using namespace std;

//// helpers ////
void Action::process(std::vector<string>& arguments)
{
  cout << "    processing arguments" << endl; // DEBUG
  // variables:
  vector<string> names; // flag names
  // find flag names and values:
  for(int i = 0; i < arguments.size(); i++)
  {
    if(arguments[i][0] == '-') // if argument is a flag name
    {
      cout << "      flag name found: " << arguments[i] << endl; // DEBUG
      arguments[i].erase(remove(arguments[i].begin(), arguments[i].end(), '-'), arguments[i].end()); // remove dash
      names.push_back(arguments[i]); // add to flag names
      arguments.erase(arguments.begin()+i); i--; // remove used argument
    }
    else // if argument is a value
    {
      cout << "      value found: " << arguments[i] << endl; // DEBUG
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
        cout << "      flag found: " << this->flags[j].getName() << endl; // DEBUG
        this->selectedFlags.push_back(this->flags[j]); // select flag
        break;
      }
    }
  }
  // check flag incompatibilities:
  for(Flag flag0: this->selectedFlags) // loop through selected flags
  {
    for(char incomp0: flag0.getIncompatibilities()) // loop through incompatibilities
    {
      for(Flag flag1: this->selectedFlags) // loop through selected flags
      {
        if(flag1.getLetter() == incomp0) // if flag is incompatibile flag
        {
          cout << "ERROR: " << "incompatibile flags: " << flag0.getLetter() << ", " << flag1.getLetter() << endl;
          exit(1);
        }
      }
    }
  }
  // activate flags:
  this->activate();
}
