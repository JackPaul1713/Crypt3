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
    virtual void execute(std::vector<std::string> arguments); // executes action
    // helpers:
    virtual void initiate(); // loads preset data
    void process(std::vector<std::string>& arguments); // processes and loads data
    virtual void activate(); // activates loaded data
    virtual void reset(); // resets processed data
    // friends:
    friend class Command;
};

#endif
