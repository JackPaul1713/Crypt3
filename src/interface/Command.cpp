#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "Command.h"
#include "Action.h"

using namespace std;

//// actions ////
void Command::execute(std::vector<string> arguments)
{
  cout << "executing command" << endl; // DEBUG
  this->process(arguments); // processes and loads data
  this->selectedAction->execute(arguments); // executes action
  this->reset(); // resets processed data
}

//// helpers ////
void Command::process(vector<string>& arguments)
{
  cout << "  processing arguments" << endl; // DEBUG
  // variables:
  string name; // action name
  bool found = false; // argument is found
  // find name:
  arguments.erase(arguments.begin()+0); // remove first argument
  for(int i = 0; i < arguments.size(); i++) // loop through command arguments
  {
    if(arguments[i][0] == '/') // if argument is an action name
    {
      if(found) // catch
      {
        cout << "ERROR: " << "too many actions" << endl;
        exit(1);
      }
      name = arguments[i];
      cout << "    action name found: " << arguments[i] << endl; // DEBUG
      name.erase(remove(name.begin(), name.end(), '/'), name.end()); // remove slash
      arguments.erase(arguments.begin()+i); i--; // remove used argument
      found = true;
    }
  }
  if(!found) // catch
  {
    cout << "ERROR: " << "no action" << endl;
    exit(1);
  }
  // find action:
  for(int i = 0; i < actions.size(); i++) // loop through actions
  {
    if(this->actions[i]->getName() == name || (this->actions[i]->getLetter() == name[0] && name.length() == 1)) // if action name matches action
    {
      this->selectedAction = this->actions[i]; // select action
      cout << "    action found: " << this->selectedAction->name << endl; // DEBUG
      return;
    }
  }
  // catch:
  cout << "ERROR: " << "invalid action: " << endl;
  exit(1);
}
