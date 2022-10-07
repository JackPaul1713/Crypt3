#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "Action.h"

class Command
{
  protected:
    // attributes:
    std::string name; // command name
    std::vector<Action*> actions; // command actions
    Action* selectedAction; // selected action
    // helpers:
    virtual void initiate() = 0; // loads preset data
    void process(std::vector<std::string>& arguments); // processes and loads data
    void reset() {this->selectedAction->reset();} // resets processed data
  public:
    // constructors:
    Command() {} // default
    Command(const Command& command): name(command.name), actions(command.actions), selectedAction(command.selectedAction) {} // copy
    // actions:
    void execute(std::vector<std::string> arguments); // executes command
    // accessors:
    std::string getName() {return(name);}
};

#endif
