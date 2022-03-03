#include <vector>
#include <iostream>
#include "Command.h"
#include "Action.h"

//// actions ////
void Command::reset() // TODO
{

}
void Command::process(vector<string> arguments)
{
  // set action:
  action = arguments[0];
  checkAction(); // check action is valid

  // set values and flags:
  for(int i = 1; i < arguments.size(); i++) // loop through arguments
  {
    if(arguments[i][0] == '-') // if argument is a flag
    {
      arguments[i].erase(remove(arguments[i].begin(), arguments[i].end(), '-'), arguments[i].end()); // remove dashes
      flags.push_back(arguments[i]); // add argument to flags
    }
    else // if argument is a value
    {
      values.push_back(argument[i]); // add argument to values
    }
  }

  // process action:
  getAction().process(values, flags);
}
void Command::execute() // TODO
{
  getAction().execute();
}

//// accessors ////
Action Command::getAction()
{
  for(int i = 0; i < actions.size(); i++) // loop through actions
  {
    if(actions[i].getName() == action) // if name matches action
    {
      return(actions[i]);
    }
  }
}

//// helpers ////
void Command::checkAction()
{
  for(int i = 0; i < actions.size(); i++) // loop through actions
  {
    if(actions[i].getName() == action) // if name matches action
    {
      return;
    }
  }
  throw std::runtime_error("invalid action");
}
