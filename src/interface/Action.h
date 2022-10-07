#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <string>
#include "Flag.h"

class Action
{
  protected:
    // attributes:
    std::string name; // action name
    char letter; // action letter
    std::vector<Flag> flags; // action flags
    std::vector<Flag> selectedFlags; // selected flags
    std::vector<std::string> values;
    // accessors:
    std::string getName() {return(name);}
    char getLetter() {return(letter);}
    // actions:
    virtual void execute(std::vector<std::string> arguments) = 0; // executes action
    // helpers:
    virtual void initiate() = 0; // loads preset data
    void process(std::vector<std::string>& arguments); // processes and loads data
    virtual void activate() = 0; // activates loaded data
    virtual void reset() = 0; // resets processed data
    // friends:
    friend class Command;
};

#endif
