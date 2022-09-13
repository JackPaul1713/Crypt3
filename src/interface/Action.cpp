#include <vector>
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
      arguments[i].erase(remove(arguments[i].begin(), arguments[i].end(), '-'), arguments[i].end()); // remove dash
      names.push_back(arguments[i]); // add to flag names
      arguments.erase(i); i--; // remove used argument
    }
    else // if argument is a value
    {
      this->values.pushback(arguments[i]); // add to values
      arguments.erase(i); i--; // remove used argument
    }
  }
  // find flags:
  for(int i = 0; i < names.size(); i++) // loop through flag names
  {
    for(int j = 0; j < this->flags.size(); j++) // loop through action flags
    {
      if(names[i] == this->flags[j].name || names[i][0] == this->flags[j].letter) // if flag name matchs flag
      {
        this->selectedFlags.push_back(this->flags[j]); // select flag
        break;
      }
    }
  }
  // check flag incompatibilities:
  for(int i = 0; i < this->selectedFlags.size(); j++) // loop through selected flags
  {
    for(int j = 0; j < this->selectedFlags.size(); k++) // loop through selected flags
    {
      for(int k = 0; k < this->selectedFlags[i].incompatibilities.size(); l++) // loop through incompatibilities
      {
        if(this->selectedFlags[j].letter == selectedFlag.incompatibilities[k].letter) // if selected flag is incompatibile flag
        {
          error = "incompatibile flags: " + this->selectedFlags[i].letter + ", " + this->selectedFlags[j].letter;
          throw std::runtime_error(error);
        }
      }
    }
  }
  // activate flags:
  this->activate();
}
