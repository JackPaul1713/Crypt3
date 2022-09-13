#include <vector>
#include <iostream>
#include "Command.h"
#include "Action.h"

using namespace std;

//// actions ////
void Command::execute(std::vector<string> arguments)
{
  this->process(arguments); // processes and loads data
  this->selectedAction->execute(arguments); // executes action
  this->reset(); // resets processed data
}

//// helpers ////
void Command::process(vector<string>& arguments)
{
  // variables:
  string name; // action name
  bool found = false; // argument is found
  string error; // error message
  // find name:
  for(int i = 0; i < arguments.size(); i++) // loop through command arguments
  {
    if(arguments[i][0] == '/') // if argument is an action name
    {
      if(found) // catch
      {
        error = "too many actions"
        throw std::runtime_error(error);
      }
      name = argument[i];
      name.erase(remove(name.begin(), name.end(), '/'), name.end()); // remove slash
      arguments.erase(i); i--; // remove used argument
      found = true;
    }
  }
  if(!found) // catch
  {
    error = "no action";
    throw std::runtime_error(error);
  }
  // find action:
  for(int i = 0; i < actions.size(); i++) // loop through actions
  {
    if(this->actions[i].getName() == name || this->actions[i].getLetter() == name) // if action name matches action
    {
      this->selectedAction = this->actions[i]; // select action
      return;
    }
  }
  // catch:
  error = "invalid action: " + name;
  throw std::runtime_error(error);
}
