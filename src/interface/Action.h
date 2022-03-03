#ifndef ACTION_H
#define ACTION_H

#include <vector>

class Action
{
  protected:
    // attributes:
    const string name;
    const vector<string> flags;
    // helpers:
    string file(string value);
  public:
    // actions:
    virtual void reset() = 0;
    virtual void process(vector<string> values, vector<string> flags) = 0;
    virtual void execute() = 0;
    // accessors:
    string getName() {return(name_);}
};

#endif
