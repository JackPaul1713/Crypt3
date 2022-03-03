#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include "Action.h"

class Command
{
  protected:
    // attributes:
    const string name;
    const vector<Action> actions;
    string action;
    vector<string> values;
    vector<string> flags;
    // helpers:
    void checkAction();
  public:
    // actions:
    void reset();
    void process(vector<string> arguments);
    void execute();
    // accessors:
    void getName() {return(name);}
    void getAction();
};

#endif
